import re
import json
from pathlib import Path
from typing import Dict, List, Optional

class IL2CPPOffsetFinder:
    def __init__(self, dump_path: str, script_json_path: str):
        self.dump_path = Path(dump_path)
        self.script_json_path = Path(script_json_path)
        self.dump_content = ""
        self.script_json = {}
        self.offsets = {}

    def load_files(self):
        """Load dump.cs and script.json"""
        print(f"[*] Loading {self.dump_path}...")
        with open(self.dump_path, 'r', encoding='utf-8') as f:
            self.dump_content = f.read()

        print(f"[*] Loading {self.script_json_path}...")
        with open(self.script_json_path, 'r', encoding='utf-8') as f:
            self.script_json = json.load(f)

    def find_class(self, class_name: str) -> Optional[str]:
        """Find a class definition in dump.cs"""
        pattern = rf'// Namespace:.*?\n(?:public )?class {re.escape(class_name)}[^\n]*\n\{{'
        match = re.search(pattern, self.dump_content, re.MULTILINE)
        if match:
            return match.group(0)
        return None

    def find_class_full(self, class_name: str, lines_after: int = 100) -> Optional[str]:
        """Find full class definition with fields and methods"""
        pattern = rf'(// Namespace:.*?\n(?:public )?class {re.escape(class_name)}[^\n]*\n\{{)'
        match = re.search(pattern, self.dump_content, re.MULTILINE)
        if not match:
            return None

        start_pos = match.start()
        # Find the end of the class (closing brace at the same indentation level)
        brace_count = 0
        in_class = False
        end_pos = start_pos

        for i, char in enumerate(self.dump_content[start_pos:], start=start_pos):
            if char == '{':
                brace_count += 1
                in_class = True
            elif char == '}':
                brace_count -= 1
                if in_class and brace_count == 0:
                    end_pos = i + 1
                    break

        return self.dump_content[start_pos:end_pos]

    def extract_fields(self, class_content: str) -> Dict[str, Dict]:
        """Extract field names and offsets from class content"""
        fields = {}
        # Pattern: // RVA: 0xXXXXXXXX Offset: 0xXXXXXXXX VA: 0xXXXXXXXX
        # followed by field declaration
        pattern = r'// RVA: (0x[0-9A-F]+) Offset: (0x[0-9A-F]+) VA: (0x[0-9A-F]+)\s*(?:public|private|protected|internal)?\s+(?:static\s+)?([^\s]+)\s+([^\s;]+);'

        for match in re.finditer(pattern, class_content):
            rva, offset, va, field_type, field_name = match.groups()
            fields[field_name] = {
                'type': field_type,
                'offset': offset,
                'rva': rva,
                'va': va
            }

        return fields

    def extract_methods(self, class_content: str) -> Dict[str, Dict]:
        """Extract method names and addresses"""
        methods = {}
        # Pattern for methods with addresses
        pattern = r'// RVA: (0x[0-9A-F]+) Offset: (0x[0-9A-F]+) VA: (0x[0-9A-F]+)\s*(?:public|private|protected|internal)?\s+(?:static\s+)?(?:virtual\s+)?([^\s]+)\s+([^\s(]+)\('

        for match in re.finditer(pattern, class_content):
            rva, offset, va, return_type, method_name = match.groups()
            methods[method_name] = {
                'return_type': return_type,
                'offset': offset,
                'rva': rva,
                'va': va
            }

        return methods

    def find_unity_methods(self) -> Dict:
        """Find common Unity methods we need to hook"""
        unity_methods = {}

        # Camera.WorldToScreenPoint
        camera_class = self.find_class_full("Camera")
        if camera_class:
            methods = self.extract_methods(camera_class)
            if "WorldToScreenPoint" in methods:
                unity_methods["Camera.WorldToScreenPoint"] = methods["WorldToScreenPoint"]

        return unity_methods

    def search_classes(self, patterns: List[str]) -> Dict:
        """Search for classes matching patterns"""
        results = {}

        for pattern in patterns:
            print(f"[*] Searching for: {pattern}")
            # Try exact match first
            class_content = self.find_class_full(pattern)
            if class_content:
                namespace_match = re.search(r'// Namespace: ([^\n]+)', class_content)
                namespace = namespace_match.group(1) if namespace_match else ""

                results[pattern] = {
                    'namespace': namespace,
                    'fields': self.extract_fields(class_content),
                    'methods': self.extract_methods(class_content),
                    'full_content': class_content[:500] + "..." if len(class_content) > 500 else class_content
                }
                print(f"  [+] Found: {namespace}.{pattern}")
            else:
                print(f"  [-] Not found: {pattern}")

        return results

    def generate_header(self, output_path: str):
        """Generate C++ header with offsets"""
        header = """#pragma once
// Auto-generated offsets from IL2CPP dump
// Generated by offset_finder.py

namespace Offsets {
"""

        for class_name, class_data in self.offsets.items():
            header += f"\n\t// {class_data.get('namespace', '')}.{class_name}\n"
            header += f"\tnamespace {class_name} {{\n"

            if class_data.get('fields'):
                header += "\t\t// Fields\n"
                for field_name, field_data in class_data['fields'].items():
                    header += f"\t\tconstexpr uintptr_t {field_name} = {field_data['offset']};\n"

            if class_data.get('methods'):
                header += "\n\t\t// Methods\n"
                for method_name, method_data in class_data['methods'].items():
                    header += f"\t\tconstexpr uintptr_t {method_name} = {method_data['offset']};\n"

            header += "\t}\n"

        header += "}\n"

        with open(output_path, 'w') as f:
            f.write(header)

        print(f"[+] Generated header: {output_path}")

    def save_json(self, output_path: str):
        """Save offsets as JSON for easier reading"""
        with open(output_path, 'w', encoding='utf-8') as f:
            json.dump(self.offsets, f, indent=2)

        print(f"[+] Saved JSON: {output_path}")

def main():
    # Initialize finder
    finder = IL2CPPOffsetFinder(
        dump_path="il2cpp-dumper/dump.cs",
        script_json_path="il2cpp-dumper/script.json"
    )

    # Load files
    finder.load_files()

    # Define what we're looking for
    search_patterns = [
        # Player/Character
        "Player",
        "PlayerController",
        "FirstPersonController",
        "CharacterController",
        "FPSController",

        # Camera
        "Camera",
        "CameraController",
        "MainCamera",

        # Targets
        "Target",
        "Sphere",
        "Ball",
        "Enemy",

        # Movement
        "Movement",
        "PlayerMovement",
        "Rigidbody",

        # Game elements
        "Finish",
        "Goal",
        "Button",
        "Interactable",
        "Door",

        # Time
        "Time",
        "TimeManager",

        # Transform (Unity)
        "Transform",
        "GameObject",
    ]

    # Search for classes
    finder.offsets = finder.search_classes(search_patterns)

    # Find Unity methods
    unity_methods = finder.find_unity_methods()
    if unity_methods:
        finder.offsets["UnityEngine"] = {"methods": unity_methods}

    # Generate outputs
    finder.generate_header("src/sdk/offsets.h")
    finder.save_json("tools/offsets.json")

    # Print summary
    print(f"\n[*] Summary:")
    print(f"  Classes found: {len(finder.offsets)}")
    for class_name, data in finder.offsets.items():
        field_count = len(data.get('fields', {}))
        method_count = len(data.get('methods', {}))
        print(f"    {class_name}: {field_count} fields, {method_count} methods")

if __name__ == "__main__":
    main()
