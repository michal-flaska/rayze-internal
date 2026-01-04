import re
import json
from pathlib import Path
from typing import Dict, List, Optional, Tuple
from difflib import SequenceMatcher
from dataclasses import dataclass

@dataclass
class ClassPattern:
	"""Pattern for finding game classes"""
	keywords: List[str]  # Keywords to search for
	priority: int  # Higher = more important
	category: str  # Category (player, camera, etc.)
	must_have_fields: List[str] = None  # Fields that should exist
	must_have_methods: List[str] = None  # Methods that should exist

	def __post_init__(self):
		if self.must_have_fields is None:
			self.must_have_fields = []
		if self.must_have_methods is None:
			self.must_have_methods = []

class IL2CPPOffsetFinder:
	def __init__(self, dump_path: str, script_json_path: str):
		self.dump_path = Path(dump_path)
		self.script_json_path = Path(script_json_path)
		self.dump_content = ""
		self.script_json = {}
		self.offsets = {}
		self.all_classes = []  # Store all found class names

		# Define search patterns
		self.patterns = [
			# Player/Character - highest priority
			ClassPattern(
				keywords=["Player", "Character", "FPS", "FirstPerson"],
				priority=100,
				category="player",
				must_have_fields=["transform", "position", "velocity"],
				must_have_methods=["Update", "Move"]
			),

			# Camera
			ClassPattern(
				keywords=["Camera", "MainCamera", "ViewCamera"],
				priority=90,
				category="camera",
				must_have_methods=["WorldToScreenPoint"]
			),

			# Targets
			ClassPattern(
				keywords=["Target", "Sphere", "Ball", "Enemy", "Orb"],
				priority=80,
				category="target",
				must_have_fields=["position", "transform"]
			),

			# Movement/Physics
			ClassPattern(
				keywords=["Movement", "Motor", "Controller"],
				priority=70,
				category="movement",
				must_have_fields=["velocity", "speed"]
			),

			# Game elements
			ClassPattern(
				keywords=["Finish", "Goal", "End", "Complete"],
				priority=60,
				category="finish"
			),

			ClassPattern(
				keywords=["Button", "Interact", "Activat", "Trigger"],
				priority=50,
				category="interactable"
			),

			# Managers
			ClassPattern(
				keywords=["GameManager", "SceneManager", "LevelManager"],
				priority=40,
				category="manager"
			),

			ClassPattern(
				keywords=["TimeManager", "TimeScale"],
				priority=40,
				category="time"
			),
		]

	def manual_search_classes(self) -> Dict:
		"""Manually search for specific class names we know exist"""
		print(f"\n[*] Manual search for known classes...")

		# Format: (class_name, expected_namespace)
		known_classes = [
			("Player", "Hyperstrange.WARPZ"),
			("Camera", "UnityEngine"),
			("Transform", "UnityEngine"),
			("TimeManager", "Hyperstrange.WARPZ"),
			("FinishPanel", "Hyperstrange.WARPZ"),
			("Panel", "Hyperstrange.WARPZ"),
			("PlayerMovementComponent", "Hyperstrange.WARPZ"),
			("PlayerWarpComponent", "Hyperstrange.WARPZ"),
			("PlayerComboComponent", "Hyperstrange.WARPZ"),
		]

		results = {}

		for class_name, expected_namespace in known_classes:
			class_content = self.find_class_full(class_name)
			if class_content:
				namespace_match = re.search(r'// Namespace: ([^\n]+)', class_content)
				namespace = namespace_match.group(1) if namespace_match else ""

				# Check if namespace matches
				if namespace == expected_namespace:
					results[class_name] = {
						'namespace': namespace,
						'fields': self.extract_fields(class_content),
						'methods': self.extract_methods(class_content),
						'content_preview': class_content[:400]
					}
					print(f"  [+] Found: {namespace}.{class_name}")
				else:
					print(f"  [-] Found {class_name} but wrong namespace: {namespace} (expected {expected_namespace})")
			else:
				print(f"  [-] Could not find {class_name}")

		return results

	def load_files(self):
		"""Load dump.cs and script.json"""
		print(f"[*] Loading {self.dump_path}...")
		with open(self.dump_path, 'r', encoding='utf-8') as f:
			self.dump_content = f.read()

		print(f"[*] Loading {self.script_json_path}...")
		with open(self.script_json_path, 'r', encoding='utf-8') as f:
			self.script_json = json.load(f)

		# Extract all class names for fuzzy matching
		self._extract_all_classes()

	def _extract_all_classes(self):
		"""Extract all class names from dump.cs"""
		pattern = r'(?:public |private |internal )?class ([A-Za-z0-9_]+)'
		matches = re.finditer(pattern, self.dump_content)
		self.all_classes = [m.group(1) for m in matches]
		print(f"[*] Found {len(self.all_classes)} total classes")

	def fuzzy_match(self, keyword: str, threshold: float = 0.6) -> List[Tuple[str, float]]:
		"""Find classes that fuzzy match a keyword"""
		matches = []
		keyword_lower = keyword.lower()

		for class_name in self.all_classes:
			class_lower = class_name.lower()

			# Exact substring match
			if keyword_lower in class_lower:
				matches.append((class_name, 1.0))
				continue

			# Fuzzy match
			ratio = SequenceMatcher(None, keyword_lower, class_lower).ratio()
			if ratio >= threshold:
				matches.append((class_name, ratio))

		# Sort by ratio (highest first)
		matches.sort(key=lambda x: x[1], reverse=True)
		return matches

	def find_class_full(self, class_name: str) -> Optional[str]:
		"""Find full class definition with fields and methods"""
		# Match only standalone class definitions (not nested classes)
		pattern = rf'(// Namespace:.*?\n(?:public |private |internal )?class {re.escape(class_name)}\s*(?::|//|\n|\{{))'

		matches = list(re.finditer(pattern, self.dump_content, re.MULTILINE))

		if not matches:
			return None

		# If multiple matches, prefer non-nested classes
		best_match = None
		for match in matches:
			start_pos = match.start()

			# Check if this is a nested class by looking backwards
			# Nested classes have more indentation before "class" keyword
			lines_before = self.dump_content[:start_pos].split('\n')
			if len(lines_before) > 0:
				last_line = lines_before[-1]
				# If the line before "class" starts with more than one tab, it's nested
				if last_line.count('\t') <= 1:
					best_match = match
					break

		if not best_match:
			best_match = matches[0]  # Fallback to first match

		start_pos = best_match.start()
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

		# IL2CPP dumps show field offsets as inline comments like: private Camera _camera; // 0x100
		# The pattern needs to match the field line, not the attribute line above it
		pattern = r'^\s*(?:public|private|protected|internal)\s+(?:static\s+)?(?:readonly\s+)?([^\s]+(?:<[^>]+>)?)\s+([^\s;]+);\s*//\s*(0x[0-9A-F]+)'

		for match in re.finditer(pattern, class_content, re.MULTILINE):
			field_type, field_name, offset = match.groups()

			# Clean up field name (remove array brackets, etc.)
			field_name_clean = field_name.split('[')[0]

			fields[field_name_clean] = {
				'type': field_type,
				'offset': offset,
				'rva': '0x0',
				'va': '0x0'
			}

		return fields

	def extract_methods(self, class_content: str) -> Dict[str, Dict]:
		"""Extract method names and addresses"""
		methods = {}
		pattern = r'// RVA: (0x[0-9A-F]+) Offset: (0x[0-9A-F]+) VA: (0x[0-9A-F]+)\s*(?:public|private|protected|internal)?\s+(?:static\s+)?(?:virtual\s+)?(?:override\s+)?([^\s]+)\s+([^\s(]+)\('

		for match in re.finditer(pattern, class_content):
			rva, offset, va, return_type, method_name = match.groups()
			methods[method_name] = {
				'return_type': return_type,
				'offset': offset,
				'rva': rva,
				'va': va
			}

		return methods

	def validate_class(self, class_content: str, pattern: ClassPattern) -> Tuple[bool, int]:
		"""Validate if class matches pattern requirements"""
		fields = self.extract_fields(class_content)
		methods = self.extract_methods(class_content)

		score = 0

		# Check must-have fields
		for required_field in pattern.must_have_fields:
			# Fuzzy match field names
			field_names_lower = [f.lower() for f in fields.keys()]
			if any(required_field.lower() in fn for fn in field_names_lower):
				score += 10
			else:
				return False, 0  # Missing required field

		# Check must-have methods
		for required_method in pattern.must_have_methods:
			method_names_lower = [m.lower() for m in methods.keys()]
			if any(required_method.lower() in mn for mn in method_names_lower):
				score += 10
			else:
				return False, 0  # Missing required method

		# Bonus points for having both fields and methods
		if fields and methods:
			score += 5

		return True, score

	def smart_search(self) -> Dict:
		"""Intelligently search for all needed classes"""
		results = {}

		for pattern in self.patterns:
			print(f"\n[*] Searching for {pattern.category} classes...")
			category_matches = []

			for keyword in pattern.keywords:
				# Fuzzy match classes
				matches = self.fuzzy_match(keyword, threshold=0.5)

				for class_name, match_ratio in matches[:10]:  # Top 10 matches
					class_content = self.find_class_full(class_name)
					if not class_content:
						continue

					# Validate class
					is_valid, validation_score = self.validate_class(class_content, pattern)

					if is_valid or not pattern.must_have_fields:  # Accept if valid or no requirements
						total_score = (match_ratio * pattern.priority) + validation_score

						namespace_match = re.search(r'// Namespace: ([^\n]+)', class_content)
						namespace = namespace_match.group(1) if namespace_match else ""

						category_matches.append({
							'class_name': class_name,
							'namespace': namespace,
							'score': total_score,
							'match_ratio': match_ratio,
							'validation_score': validation_score,
							'fields': self.extract_fields(class_content),
							'methods': self.extract_methods(class_content),
							'content_preview': class_content[:300]
						})

			# Sort by score and take best match
			if category_matches:
				category_matches.sort(key=lambda x: x['score'], reverse=True)
				best_match = category_matches[0]

				print(f"  [+] Best match for {pattern.category}: {best_match['class_name']}")
				print(f"	  Namespace: {best_match['namespace']}")
				print(f"	  Score: {best_match['score']:.2f} (match: {best_match['match_ratio']:.2f}, validation: {best_match['validation_score']})")
				print(f"	  Fields: {len(best_match['fields'])}, Methods: {len(best_match['methods'])}")

				results[best_match['class_name']] = best_match

				# Show alternatives
				if len(category_matches) > 1:
					print(f"	  Alternatives:")
					for alt in category_matches[1:3]:
						print(f"		- {alt['class_name']} (score: {alt['score']:.2f})")
			else:
				print(f"  [-] No matches found for {pattern.category}")

		return results

	def generate_header(self, output_path: str):
		"""Generate C++ header with offsets"""
		header = """#pragma once
// Auto-generated offsets from IL2CPP dump
// Generated by offset_finder.py
// DO NOT EDIT MANUALLY - Run `python tools/offset_finder.py` to regenerate

#include <cstdint>

namespace Offsets {
"""

		for class_name, class_data in self.offsets.items():
			namespace = class_data.get('namespace', '')
			header += f"\n\t// {namespace}.{class_name}\n"

			# Add category comment if available
			if 'category' in class_data:
				header += f"\t// Category: {class_data['category']}\n"

			header += f"\tnamespace {class_name} {{\n"

			if class_data.get('fields'):
				header += "\t\t// Fields\n"
				for field_name, field_data in class_data['fields'].items():
					field_type = field_data.get('type', 'unknown')
					header += f"\t\tconstexpr uintptr_t {field_name} = {field_data['offset']}; // {field_type}\n"

			if class_data.get('methods'):
				header += "\n\t\t// Methods\n"
				for method_name, method_data in class_data['methods'].items():
					return_type = method_data.get('return_type', 'void')
					header += f"\t\tconstexpr uintptr_t {method_name} = {method_data['offset']}; // {return_type}\n"

			header += "\t}\n"

		header += "}\n"

		Path(output_path).parent.mkdir(parents=True, exist_ok=True)
		with open(output_path, 'w') as f:
			f.write(header)

		print(f"\n[+] Generated header: {output_path}")

	def save_json(self, output_path: str):
		"""Save offsets as JSON for easier reading"""
		Path(output_path).parent.mkdir(parents=True, exist_ok=True)
		with open(output_path, 'w', encoding='utf-8') as f:
			json.dump(self.offsets, f, indent=2)

		print(f"[+] Saved JSON: {output_path}")

	def generate_summary_report(self, output_path: str):
		"""Generate human-readable summary report"""
		report = "# IL2CPP Offset Finder Report\n\n"

		for class_name, class_data in self.offsets.items():
			report += f"## {class_name}\n"
			report += f"- **Namespace**: {class_data.get('namespace', 'Unknown')}\n"

			if 'category' in class_data:
				report += f"- **Category**: {class_data['category']}\n"

			if 'match_ratio' in class_data:
				report += f"- **Match Confidence**: {class_data['match_ratio']:.2%}\n"

			if 'content_preview' in class_data:
				report += f"\n### Preview\n```csharp\n{class_data['content_preview']}\n```\n"

			if class_data.get('fields'):
				report += f"\n### Fields ({len(class_data['fields'])})\n"
				for field_name, field_data in list(class_data['fields'].items())[:10]:
					report += f"- `{field_name}`: {field_data['type']} @ {field_data['offset']}\n"

				if len(class_data['fields']) > 10:
					report += f"- ... and {len(class_data['fields']) - 10} more\n"

			if class_data.get('methods'):
				report += f"\n### Methods ({len(class_data['methods'])})\n"
				for method_name, method_data in list(class_data['methods'].items())[:10]:
					report += f"- `{method_name}()`: {method_data['return_type']} @ {method_data['offset']}\n"

				if len(class_data['methods']) > 10:
					report += f"- ... and {len(class_data['methods']) - 10} more\n"

			report += "\n---\n\n"

		Path(output_path).parent.mkdir(parents=True, exist_ok=True)
		with open(output_path, 'w', encoding='utf-8') as f:
			f.write(report)

		print(f"[+] Generated report: {output_path}")

def main():
	print("=" * 60)
	print("IL2CPP Smart Offset Finder")
	print("=" * 60)

	finder = IL2CPPOffsetFinder(
		dump_path="il2cpp-dumper/dump.cs",
		script_json_path="il2cpp-dumper/script.json"
	)

	finder.load_files()

	# Manual search for known classes (highest priority)
	game_classes = finder.manual_search_classes()

	# Smart search for additional classes (panels, buttons, etc.)
	smart_results = finder.smart_search()

	# Merge results (manual takes priority)
	finder.offsets = {**smart_results, **game_classes}

	# Generate outputs
	finder.generate_header("src/sdk/offsets.h")
	finder.save_json("tools/offsets.json")
	finder.generate_summary_report("tools/OFFSET_REPORT.md")

	print("\n" + "=" * 60)
	print(f"Summary: {len(finder.offsets)} classes found")
	print("=" * 60)

if __name__ == "__main__":
	main()

