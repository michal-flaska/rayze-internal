wont search a ~400k lines of code each game update, so i vibecoded some python script
```bash
python tools/offset_finder.py
```

---

manual searching:

```
// Namespace: Hyperstrange.WARPZ
public class Player : BaseBehaviour // TypeDefIndex: 7939
{
	// Fields
	public static Action<Player> OnStart; // 0x0
	public static Action<Player> OnFinish; // 0x8
	public static Action<Player> OnDeath; // 0x10
	public Action<PlayerWarpComponent> OnFinishWarpSuccess; // 0x40
	public Action<PlayerWarpComponent> OnButtonSuccess; // 0x48
	public Action<PlayerWarpComponent> OnWarpSuccess; // 0x50
	public Action<PlayerWarpComponent> OnWarpFail; // 0x58
	public Action<PlayerWarpComponent> OnWarpFinderUpdate; // 0x60
	public Action<PlayerComboComponent> OnComboIncremented; // 0x68
	public Action<PlayerComboComponent> OnComboTimeOutUpdate; // 0x70
	public Action<PlayerComboComponent> OnComboTimedOut; // 0x78
	public Action<PlayerOxygenComponent> OnOxygenEnd; // 0x80
	public Action<PlayerOxygenComponent> OnOxygenUpdate; // 0x88
	public Action<PlayerOxygenView> OnLowOxygenPulse; // 0x90
	public Action<PlayerBreakComponent> OnBreak; // 0x98
	public Action<Player> OnRespawn; // 0xA0
	public Action OnDebugNoClipChanged; // 0xA8
	public Action OnDebugViewChanged; // 0xB0
	public Action OnDebugComboIncremented; // 0xB8
	public Action OnDebugTimeScaleChanged; // 0xC0
	public Action OnDebugOxygenChanged; // 0xC8
	[SerializeField] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private Transform _cameraTransform; // 0xD0
	private PlayerSpawnPoint _playerSpawnPoint; // 0xD8
	private PlayerMovementComponent _movementComponent; // 0xE0
	private PlayerTimeComponent _timeComponent; // 0xE8
	private PlayerStatsComponent _statsComponent; // 0xF0
	private PlayerDebugComponent _debugComponent; // 0xF8
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private Camera <Camera>k__BackingField; // 0x100
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private bool <IsActive>k__BackingField; // 0x108
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private PlayerWarpComponent <WarpComponent>k__BackingField; // 0x110
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private PlayerComboComponent <ComboComponent>k__BackingField; // 0x118

	// Properties
	public Camera Camera { get; set; }
	public Transform CameraTransform { get; }
	public bool IsActive { get; set; }
	public bool IsMoving { get; }
	public bool MinimalSpeed { get; }
	public ObscuredFloat CurrentSpeed { get; }
	public SpeedStat SpeedStat { get; }
	public TimeStat CurrentTime { get; }
	public PlayerWarpComponent WarpComponent { get; set; }
	public PlayerComboComponent ComboComponent { get; set; }
	public bool DebugNoClip { get; }
	public bool DebugHiddenView { get; }
	public bool DebugOxygenDisabled { get; }

	// Methods

	// RVA: 0x138DFC0 Offset: 0x138C7C0 VA: 0x18138DFC0
	private void Awake() { }

	// RVA: 0x138E4D0 Offset: 0x138CCD0 VA: 0x18138E4D0
	private void OnEnable() { }

	// RVA: 0x138E200 Offset: 0x138CA00 VA: 0x18138E200
	private void OnDisable() { }

	// RVA: 0x138E7B0 Offset: 0x138CFB0 VA: 0x18138E7B0
	private void OnLevelPrepareStart() { }

	// RVA: 0x138E8C0 Offset: 0x138D0C0 VA: 0x18138E8C0
	private void OnLevelStart() { }

	// RVA: 0x138E7A0 Offset: 0x138CFA0 VA: 0x18138E7A0
	private void OnLevelPrepareEnd() { }

	// RVA: 0x138E7A0 Offset: 0x138CFA0 VA: 0x18138E7A0
	private void OnFinishWarp(PlayerWarpComponent warpComponent) { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2DBCF0 Offset: 0x2DA4F0 VA: 0x1802DBCF0
	public Camera get_Camera() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2DC1C0 Offset: 0x2DA9C0 VA: 0x1802DC1C0
	private void set_Camera(Camera value) { }

	// RVA: 0x587720 Offset: 0x585F20 VA: 0x180587720
	public Transform get_CameraTransform() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2DBD10 Offset: 0x2DA510 VA: 0x1802DBD10
	public bool get_IsActive() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2DC1E0 Offset: 0x2DA9E0 VA: 0x1802DC1E0
	private void set_IsActive(bool value) { }

	// RVA: 0x138F980 Offset: 0x138E180 VA: 0x18138F980
	public bool get_IsMoving() { }

	// RVA: 0x138F9B0 Offset: 0x138E1B0 VA: 0x18138F9B0
	public bool get_MinimalSpeed() { }

	// RVA: 0x138F8C0 Offset: 0x138E0C0 VA: 0x18138F8C0
	public ObscuredFloat get_CurrentSpeed() { }

	// RVA: 0x138FA10 Offset: 0x138E210 VA: 0x18138FA10
	public SpeedStat get_SpeedStat() { }

	// RVA: 0x138F900 Offset: 0x138E100 VA: 0x18138F900
	public TimeStat get_CurrentTime() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2FAD10 Offset: 0x2F9510 VA: 0x1802FAD10
	public PlayerWarpComponent get_WarpComponent() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x2DC310 Offset: 0x2DAB10 VA: 0x1802DC310
	private void set_WarpComponent(PlayerWarpComponent value) { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x4FA750 Offset: 0x4F8F50 VA: 0x1804FA750
	public PlayerComboComponent get_ComboComponent() { }

	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x4FC920 Offset: 0x4FB120 VA: 0x1804FC920
	private void set_ComboComponent(PlayerComboComponent value) { }

	// RVA: 0x138E1B0 Offset: 0x138C9B0 VA: 0x18138E1B0
	public LevelRunInfo GetLastRunInfo() { }

	// RVA: 0x138E170 Offset: 0x138C970 VA: 0x18138E170
	public LevelAchievementsStats GetAchievementsStats() { }

	// RVA: 0x138F940 Offset: 0x138E140 VA: 0x18138F940
	public bool get_DebugNoClip() { }

	// RVA: 0x138F920 Offset: 0x138E120 VA: 0x18138F920
	public bool get_DebugHiddenView() { }

	// RVA: 0x138F960 Offset: 0x138E160 VA: 0x18138F960
	public bool get_DebugOxygenDisabled() { }

	// RVA: 0x138EA70 Offset: 0x138D270 VA: 0x18138EA70
	public void .ctor() { }

	// RVA: 0x138E8D0 Offset: 0x138D0D0 VA: 0x18138E8D0
	private static void .cctor() { }
}
```

```
// Namespace: UnityEngine
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[UsedByNativeCodeAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[RequireComponent] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
[NativeHeaderAttribute] // RVA: 0x12C550 Offset: 0x12B950 VA: 0x18012C550
public sealed class Camera : Behaviour // TypeDefIndex: 3017
{
	// Fields
	public static Camera.CameraCallback onPreCull; // 0x0
	public static Camera.CameraCallback onPreRender; // 0x8
	public static Camera.CameraCallback onPostRender; // 0x10

	// Properties
	[NativePropertyAttribute] // RVA: 0x12CA50 Offset: 0x12BE50 VA: 0x18012CA50
	public float nearClipPlane { get; set; }
	[NativePropertyAttribute] // RVA: 0x12CA80 Offset: 0x12BE80 VA: 0x18012CA80
	public float farClipPlane { get; set; }
	[NativePropertyAttribute] // RVA: 0x12CAB0 Offset: 0x12BEB0 VA: 0x18012CAB0
	public float fieldOfView { get; set; }
	public RenderingPath renderingPath { set; }
	public bool allowHDR { get; set; }
	public bool allowMSAA { get; set; }
	public bool allowDynamicResolution { get; }
	public float orthographicSize { get; set; }
	public bool orthographic { get; set; }
	public OpaqueSortMode opaqueSortMode { get; }
	public float depth { get; set; }
	public float aspect { get; set; }
	public int cullingMask { get; }
	public int eventMask { get; }
	public CameraType cameraType { get; set; }
	public bool useOcclusionCulling { set; }
	public Color backgroundColor { get; set; }
	public CameraClearFlags clearFlags { get; set; }
	public bool usePhysicalProperties { get; }
	[NativePropertyAttribute] // RVA: 0x12CAE0 Offset: 0x12BEE0 VA: 0x18012CAE0
	public Rect rect { get; set; }
	[NativePropertyAttribute] // RVA: 0x12CB60 Offset: 0x12BF60 VA: 0x18012CB60
	public Rect pixelRect { get; set; }
	public int pixelWidth { get; }
	public int pixelHeight { get; }
	public RenderTexture targetTexture { get; set; }
	public int targetDisplay { get; }
	public Matrix4x4 worldToCameraMatrix { get; set; }
	public Matrix4x4 projectionMatrix { get; set; }
	public static Camera main { get; }
	public static Camera current { get; }
	public bool stereoEnabled { get; }
	public StereoTargetEyeMask stereoTargetEye { get; }
	public static int allCamerasCount { get; }

	// Methods

	// RVA: 0x7A8270 Offset: 0x7A6A70 VA: 0x1807A8270
	public void .ctor() { }

	// RVA: 0x7AC890 Offset: 0x7AB090 VA: 0x1807AC890
	public float get_nearClipPlane() { }

	// RVA: 0x7AD0F0 Offset: 0x7AB8F0 VA: 0x1807AD0F0
	public void set_nearClipPlane(float value) { }

	// RVA: 0x7AC7E0 Offset: 0x7AAFE0 VA: 0x1807AC7E0
	public float get_farClipPlane() { }

	// RVA: 0x7AD050 Offset: 0x7AB850 VA: 0x1807AD050
	public void set_farClipPlane(float value) { }

	// RVA: 0x7AC820 Offset: 0x7AB020 VA: 0x1807AC820
	public float get_fieldOfView() { }

	// RVA: 0x7AD0A0 Offset: 0x7AB8A0 VA: 0x1807AD0A0
	public void set_fieldOfView(float value) { }

	// RVA: 0x7AD3C0 Offset: 0x7ABBC0 VA: 0x1807AD3C0
	public void set_renderingPath(RenderingPath value) { }

	// RVA: 0x7AC510 Offset: 0x7AAD10 VA: 0x1807AC510
	public bool get_allowHDR() { }

	// RVA: 0x7ACDF0 Offset: 0x7AB5F0 VA: 0x1807ACDF0
	public void set_allowHDR(bool value) { }

	// RVA: 0x7AC550 Offset: 0x7AAD50 VA: 0x1807AC550
	public bool get_allowMSAA() { }

	// RVA: 0x7ACE40 Offset: 0x7AB640 VA: 0x1807ACE40
	public void set_allowMSAA(bool value) { }

	// RVA: 0x7AC4D0 Offset: 0x7AACD0 VA: 0x1807AC4D0
	public bool get_allowDynamicResolution() { }

	// RVA: 0x7AC910 Offset: 0x7AB110 VA: 0x1807AC910
	public float get_orthographicSize() { }

	// RVA: 0x7AD140 Offset: 0x7AB940 VA: 0x1807AD140
	public void set_orthographicSize(float value) { }

	// RVA: 0x7AC950 Offset: 0x7AB150 VA: 0x1807AC950
	public bool get_orthographic() { }

	// RVA: 0x7AD190 Offset: 0x7AB990 VA: 0x1807AD190
	public void set_orthographic(bool value) { }

	// RVA: 0x7AC8D0 Offset: 0x7AB0D0 VA: 0x1807AC8D0
	public OpaqueSortMode get_opaqueSortMode() { }

	// RVA: 0x7AC760 Offset: 0x7AAF60 VA: 0x1807AC760
	public float get_depth() { }

	// RVA: 0x7AD000 Offset: 0x7AB800 VA: 0x1807AD000
	public void set_depth(float value) { }

	// RVA: 0x7AC590 Offset: 0x7AAD90 VA: 0x1807AC590
	public float get_aspect() { }

	// RVA: 0x7ACE90 Offset: 0x7AB690 VA: 0x1807ACE90
	public void set_aspect(float value) { }

	// RVA: 0x7AC6F0 Offset: 0x7AAEF0 VA: 0x1807AC6F0
	public int get_cullingMask() { }

	// RVA: 0x7AC7A0 Offset: 0x7AAFA0 VA: 0x1807AC7A0
	public int get_eventMask() { }

	// RVA: 0x7AC670 Offset: 0x7AAE70 VA: 0x1807AC670
	public CameraType get_cameraType() { }

	// RVA: 0x7ACF80 Offset: 0x7AB780 VA: 0x1807ACF80
	public void set_cameraType(CameraType value) { }

	// RVA: 0x7AD450 Offset: 0x7ABC50 VA: 0x1807AD450
	public void set_useOcclusionCulling(bool value) { }

	// RVA: 0x7AC620 Offset: 0x7AAE20 VA: 0x1807AC620
	public Color get_backgroundColor() { }

	// RVA: 0x7ACF30 Offset: 0x7AB730 VA: 0x1807ACF30
	public void set_backgroundColor(Color value) { }

	// RVA: 0x7AC6B0 Offset: 0x7AAEB0 VA: 0x1807AC6B0
	public CameraClearFlags get_clearFlags() { }

	// RVA: 0x7ACFC0 Offset: 0x7AB7C0 VA: 0x1807ACFC0
	public void set_clearFlags(CameraClearFlags value) { }

	// RVA: 0x7ACD00 Offset: 0x7AB500 VA: 0x1807ACD00
	public bool get_usePhysicalProperties() { }

	// RVA: 0x7ACBB0 Offset: 0x7AB3B0 VA: 0x1807ACBB0
	public Rect get_rect() { }

	// RVA: 0x7AD370 Offset: 0x7ABB70 VA: 0x1807AD370
	public void set_rect(Rect value) { }

	// RVA: 0x7ACA20 Offset: 0x7AB220 VA: 0x1807ACA20
	public Rect get_pixelRect() { }

	// RVA: 0x7AD230 Offset: 0x7ABA30 VA: 0x1807AD230
	public void set_pixelRect(Rect value) { }

	[FreeFunctionAttribute] // RVA: 0x12C6B0 Offset: 0x12BAB0 VA: 0x18012C6B0
	// RVA: 0x7ACA70 Offset: 0x7AB270 VA: 0x1807ACA70
	public int get_pixelWidth() { }

	[FreeFunctionAttribute] // RVA: 0x12C6F0 Offset: 0x12BAF0 VA: 0x18012C6F0
	// RVA: 0x7AC990 Offset: 0x7AB190 VA: 0x1807AC990
	public int get_pixelHeight() { }

	// RVA: 0x7ACCC0 Offset: 0x7AB4C0 VA: 0x1807ACCC0
	public RenderTexture get_targetTexture() { }

	// RVA: 0x7AD400 Offset: 0x7ABC00 VA: 0x1807AD400
	public void set_targetTexture(RenderTexture value) { }

	// RVA: 0x7ACC80 Offset: 0x7AB480 VA: 0x1807ACC80
	public int get_targetDisplay() { }

	// RVA: 0x7ACD90 Offset: 0x7AB590 VA: 0x1807ACD90
	public Matrix4x4 get_worldToCameraMatrix() { }

	// RVA: 0x7AD4F0 Offset: 0x7ABCF0 VA: 0x1807AD4F0
	public void set_worldToCameraMatrix(Matrix4x4 value) { }

	// RVA: 0x7ACB00 Offset: 0x7AB300 VA: 0x1807ACB00
	public Matrix4x4 get_projectionMatrix() { }

	// RVA: 0x7AD2D0 Offset: 0x7ABAD0 VA: 0x1807AD2D0
	public void set_projectionMatrix(Matrix4x4 value) { }

	// RVA: 0x7ABE70 Offset: 0x7AA670 VA: 0x1807ABE70
	public void ResetWorldToCameraMatrix() { }

	// RVA: 0x7ABDB0 Offset: 0x7AA5B0 VA: 0x1807ABDB0
	public void ResetProjectionMatrix() { }

	// RVA: 0x7AC3D0 Offset: 0x7AABD0 VA: 0x1807AC3D0
	public Vector3 WorldToScreenPoint(Vector3 position, Camera.MonoOrStereoscopicEye eye) { }

	// RVA: 0x7AC440 Offset: 0x7AAC40 VA: 0x1807AC440
	public Vector3 WorldToScreenPoint(Vector3 position) { }

	// RVA: 0x7AC160 Offset: 0x7AA960 VA: 0x1807AC160
	public Vector3 ScreenToViewportPoint(Vector3 position) { }

	// RVA: 0x7AC090 Offset: 0x7AA890 VA: 0x1807AC090
	private Ray ScreenPointToRay(Vector2 pos, Camera.MonoOrStereoscopicEye eye) { }

	// RVA: 0x7ABF20 Offset: 0x7AA720 VA: 0x1807ABF20
	public Ray ScreenPointToRay(Vector3 pos, Camera.MonoOrStereoscopicEye eye) { }

	// RVA: 0x7ABFE0 Offset: 0x7AA7E0 VA: 0x1807ABFE0
	public Ray ScreenPointToRay(Vector3 pos) { }

	[FreeFunctionAttribute] // RVA: 0x12C730 Offset: 0x12BB30 VA: 0x18012C730
	// RVA: 0x7AC860 Offset: 0x7AB060 VA: 0x1807AC860
	public static Camera get_main() { }

	[FreeFunctionAttribute] // RVA: 0x12C760 Offset: 0x12BB60 VA: 0x18012C760
	// RVA: 0x7AC730 Offset: 0x7AAF30 VA: 0x1807AC730
	public static Camera get_current() { }

	// RVA: 0x7ACC00 Offset: 0x7AB400 VA: 0x1807ACC00
	public bool get_stereoEnabled() { }

	// RVA: 0x7ACC40 Offset: 0x7AB440 VA: 0x1807ACC40
	public StereoTargetEyeMask get_stereoTargetEye() { }

	// RVA: 0x7AC210 Offset: 0x7AAA10 VA: 0x1807AC210
	public void SetStereoProjectionMatrix(Camera.StereoscopicEye eye, Matrix4x4 matrix) { }

	// RVA: 0x7ABDF0 Offset: 0x7AA5F0 VA: 0x1807ABDF0
	public void ResetStereoProjectionMatrices() { }

	// RVA: 0x7AC2B0 Offset: 0x7AAAB0 VA: 0x1807AC2B0
	public void SetStereoViewMatrix(Camera.StereoscopicEye eye, Matrix4x4 matrix) { }

	// RVA: 0x7ABE30 Offset: 0x7AA630 VA: 0x1807ABE30
	public void ResetStereoViewMatrices() { }

	[FreeFunctionAttribute] // RVA: 0x12C810 Offset: 0x12BC10 VA: 0x18012C810
	// RVA: 0x7ABBB0 Offset: 0x7AA3B0 VA: 0x1807ABBB0
	private static int GetAllCamerasCount() { }

	[FreeFunctionAttribute] // RVA: 0x12C840 Offset: 0x12BC40 VA: 0x18012C840
	// RVA: 0x7ABBE0 Offset: 0x7AA3E0 VA: 0x1807ABBE0
	private static int GetAllCamerasImpl([Out] Camera[] cam) { }

	// RVA: 0x7ABBB0 Offset: 0x7AA3B0 VA: 0x1807ABBB0
	public static int get_allCamerasCount() { }

	// RVA: 0x7ABC20 Offset: 0x7AA420 VA: 0x1807ABC20
	public static int GetAllCameras(Camera[] cameras) { }

	[FreeFunctionAttribute] // RVA: 0x12C870 Offset: 0x12BC70 VA: 0x18012C870
	// RVA: 0x7ABD70 Offset: 0x7AA570 VA: 0x1807ABD70
	public void Render() { }

	[RequiredByNativeCodeAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x7ABAF0 Offset: 0x7AA2F0 VA: 0x1807ABAF0
	private static void FireOnPreCull(Camera cam) { }

	[RequiredByNativeCodeAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x7ABB50 Offset: 0x7AA350 VA: 0x1807ABB50
	private static void FireOnPreRender(Camera cam) { }

	[RequiredByNativeCodeAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	// RVA: 0x7ABA90 Offset: 0x7AA290 VA: 0x1807ABA90
	private static void FireOnPostRender(Camera cam) { }

	// RVA: 0x7AC300 Offset: 0x7AAB00 VA: 0x1807AC300
	public bool TryGetCullingParameters(bool stereoAware, out ScriptableCullingParameters cullingParameters) { }

	[NativeHeaderAttribute] // RVA: 0x12C960 Offset: 0x12BD60 VA: 0x18012C960
	[FreeFunctionAttribute] // RVA: 0x12C960 Offset: 0x12BD60 VA: 0x18012C960
	// RVA: 0x7ABD00 Offset: 0x7AA500 VA: 0x1807ABD00
	private static bool GetCullingParameters_Internal(Camera camera, bool stereoAware, out ScriptableCullingParameters cullingParameters, int managedCullingParametersSize) { }

	// RVA: 0x7AC5D0 Offset: 0x7AADD0 VA: 0x1807AC5D0
	private void get_backgroundColor_Injected(out Color ret) { }

	// RVA: 0x7ACEE0 Offset: 0x7AB6E0 VA: 0x1807ACEE0
	private void set_backgroundColor_Injected(ref Color value) { }

	// RVA: 0x7ACB60 Offset: 0x7AB360 VA: 0x1807ACB60
	private void get_rect_Injected(out Rect ret) { }

	// RVA: 0x7AD320 Offset: 0x7ABB20 VA: 0x1807AD320
	private void set_rect_Injected(ref Rect value) { }

	// RVA: 0x7AC9D0 Offset: 0x7AB1D0 VA: 0x1807AC9D0
	private void get_pixelRect_Injected(out Rect ret) { }

	// RVA: 0x7AD1E0 Offset: 0x7AB9E0 VA: 0x1807AD1E0
	private void set_pixelRect_Injected(ref Rect value) { }

	// RVA: 0x7ACD40 Offset: 0x7AB540 VA: 0x1807ACD40
	private void get_worldToCameraMatrix_Injected(out Matrix4x4 ret) { }

	// RVA: 0x7AD4A0 Offset: 0x7ABCA0 VA: 0x1807AD4A0
	private void set_worldToCameraMatrix_Injected(ref Matrix4x4 value) { }

	// RVA: 0x7ACAB0 Offset: 0x7AB2B0 VA: 0x1807ACAB0
	private void get_projectionMatrix_Injected(out Matrix4x4 ret) { }

	// RVA: 0x7AD280 Offset: 0x7ABA80 VA: 0x1807AD280
	private void set_projectionMatrix_Injected(ref Matrix4x4 value) { }

	// RVA: 0x7AC360 Offset: 0x7AAB60 VA: 0x1807AC360
	private void WorldToScreenPoint_Injected(ref Vector3 position, Camera.MonoOrStereoscopicEye eye, out Vector3 ret) { }

	// RVA: 0x7AC100 Offset: 0x7AA900 VA: 0x1807AC100
	private void ScreenToViewportPoint_Injected(ref Vector3 position, out Vector3 ret) { }

	// RVA: 0x7ABEB0 Offset: 0x7AA6B0 VA: 0x1807ABEB0
	private void ScreenPointToRay_Injected(ref Vector2 pos, Camera.MonoOrStereoscopicEye eye, out Ray ret) { }

	// RVA: 0x7AC1C0 Offset: 0x7AA9C0 VA: 0x1807AC1C0
	private void SetStereoProjectionMatrix_Injected(Camera.StereoscopicEye eye, ref Matrix4x4 matrix) { }

	// RVA: 0x7AC260 Offset: 0x7AAA60 VA: 0x1807AC260
	private void SetStereoViewMatrix_Injected(Camera.StereoscopicEye eye, ref Matrix4x4 matrix) { }
}
```

```
// Namespace: UnityEngine
[RequiredByNativeCodeAttribute] // RVA: 0x126900 Offset: 0x125D00 VA: 0x180126900
[NativeHeaderAttribute] // RVA: 0x126900 Offset: 0x125D00 VA: 0x180126900
[NativeHeaderAttribute] // RVA: 0x126900 Offset: 0x125D00 VA: 0x180126900
[NativeHeaderAttribute] // RVA: 0x126900 Offset: 0x125D00 VA: 0x180126900
public class Transform : Component, IEnumerable // TypeDefIndex: 3216
{
	// Properties
	public Vector3 position { get; set; }
	public Vector3 localPosition { get; set; }
	public Vector3 eulerAngles { get; set; }
	public Vector3 localEulerAngles { get; set; }
	public Vector3 right { get; }
	public Vector3 up { get; }
	public Vector3 forward { get; }
	public Quaternion rotation { get; set; }
	public Quaternion localRotation { get; set; }
	public Vector3 localScale { get; set; }
	public Transform parent { get; set; }
	internal Transform parentInternal { get; set; }
	public Matrix4x4 worldToLocalMatrix { get; }
	public Matrix4x4 localToWorldMatrix { get; }
	public Transform root { get; }
	public int childCount { get; }
	public Vector3 lossyScale { get; }
	[NativePropertyAttribute] // RVA: 0x126B50 Offset: 0x125F50 VA: 0x180126B50
	public bool hasChanged { set; }

	// Methods

	// RVA: 0x7FA9A0 Offset: 0x7F91A0 VA: 0x1807FA9A0
	protected void .ctor() { }

	// RVA: 0x9FC630 Offset: 0x9FAE30 VA: 0x1809FC630
	public Vector3 get_position() { }

	// RVA: 0x9FCDA0 Offset: 0x9FB5A0 VA: 0x1809FCDA0
	public void set_position(Vector3 value) { }

	// RVA: 0x9FC300 Offset: 0x9FAB00 VA: 0x1809FC300
	public Vector3 get_localPosition() { }

	// RVA: 0x9FCAF0 Offset: 0x9FB2F0 VA: 0x1809FCAF0
	public void set_localPosition(Vector3 value) { }

	// RVA: 0x9FC0C0 Offset: 0x9FA8C0 VA: 0x1809FC0C0
	public Vector3 get_eulerAngles() { }

	// RVA: 0x9FC970 Offset: 0x9FB170 VA: 0x1809FC970
	public void set_eulerAngles(Vector3 value) { }

	// RVA: 0x9FC220 Offset: 0x9FAA20 VA: 0x1809FC220
	public Vector3 get_localEulerAngles() { }

	// RVA: 0x9FCA30 Offset: 0x9FB230 VA: 0x1809FCA30
	public void set_localEulerAngles(Vector3 value) { }

	// RVA: 0x9FC680 Offset: 0x9FAE80 VA: 0x1809FC680
	public Vector3 get_right() { }

	// RVA: 0x9FC7F0 Offset: 0x9FAFF0 VA: 0x1809FC7F0
	public Vector3 get_up() { }

	// RVA: 0x9FC150 Offset: 0x9FA950 VA: 0x1809FC150
	public Vector3 get_forward() { }

	// RVA: 0x9FC7A0 Offset: 0x9FAFA0 VA: 0x1809FC7A0
	public Quaternion get_rotation() { }

	// RVA: 0x9FCE40 Offset: 0x9FB640 VA: 0x1809FCE40
	public void set_rotation(Quaternion value) { }

	// RVA: 0x9FC3A0 Offset: 0x9FABA0 VA: 0x1809FC3A0
	public Quaternion get_localRotation() { }

	// RVA: 0x9FCB90 Offset: 0x9FB390 VA: 0x1809FCB90
	public void set_localRotation(Quaternion value) { }

	// RVA: 0x9FC440 Offset: 0x9FAC40 VA: 0x1809FC440
	public Vector3 get_localScale() { }

	// RVA: 0x9FCC30 Offset: 0x9FB430 VA: 0x1809FCC30
	public void set_localScale(Vector3 value) { }

	// RVA: 0x9FB410 Offset: 0x9F9C10 VA: 0x1809FB410
	public Transform get_parent() { }

	// RVA: 0x9FCC80 Offset: 0x9FB480 VA: 0x1809FCC80
	public void set_parent(Transform value) { }

	// RVA: 0x9FB410 Offset: 0x9F9C10 VA: 0x1809FB410
	internal Transform get_parentInternal() { }

	// RVA: 0x9FBCA0 Offset: 0x9FA4A0 VA: 0x1809FBCA0
	internal void set_parentInternal(Transform value) { }

	// RVA: 0x9FB410 Offset: 0x9F9C10 VA: 0x1809FB410
	private Transform GetParent() { }

	// RVA: 0x9FBCA0 Offset: 0x9FA4A0 VA: 0x1809FBCA0
	public void SetParent(Transform p) { }

	[FreeFunctionAttribute] // RVA: 0x126990 Offset: 0x125D90 VA: 0x180126990
	// RVA: 0x9FBCF0 Offset: 0x9FA4F0 VA: 0x1809FBCF0
	public void SetParent(Transform parent, bool worldPositionStays) { }

	// RVA: 0x9FC910 Offset: 0x9FB110 VA: 0x1809FC910
	public Matrix4x4 get_worldToLocalMatrix() { }

	// RVA: 0x9FC4E0 Offset: 0x9FACE0 VA: 0x1809FC4E0
	public Matrix4x4 get_localToWorldMatrix() { }

	// RVA: 0x9FBF10 Offset: 0x9FA710 VA: 0x1809FBF10
	public void Translate(Vector3 translation, Space relativeTo) { }

	// RVA: 0x9FB960 Offset: 0x9FA160 VA: 0x1809FB960
	public void Rotate(Vector3 eulers, Space relativeTo) { }

	// RVA: 0x9FB720 Offset: 0x9F9F20 VA: 0x1809FB720
	public void Rotate(Vector3 eulers) { }

	// RVA: 0x9FBBA0 Offset: 0x9FA3A0 VA: 0x1809FBBA0
	public void Rotate(float xAngle, float yAngle, float zAngle) { }

	[NativeMethodAttribute] // RVA: 0x126A00 Offset: 0x125E00 VA: 0x180126A00
	// RVA: 0x9FB6C0 Offset: 0x9F9EC0 VA: 0x1809FB6C0
	internal void RotateAroundInternal(Vector3 axis, float angle) { }

	// RVA: 0x9FB820 Offset: 0x9FA020 VA: 0x1809FB820
	public void Rotate(Vector3 axis, float angle, Space relativeTo) { }

	// RVA: 0x9FBDF0 Offset: 0x9FA5F0 VA: 0x1809FBDF0
	public Vector3 TransformDirection(Vector3 direction) { }

	// RVA: 0x9FB4F0 Offset: 0x9F9CF0 VA: 0x1809FB4F0
	public Vector3 InverseTransformDirection(Vector3 direction) { }

	// RVA: 0x9FBEB0 Offset: 0x9FA6B0 VA: 0x1809FBEB0
	public Vector3 TransformPoint(Vector3 position) { }

	// RVA: 0x9FB5B0 Offset: 0x9F9DB0 VA: 0x1809FB5B0
	public Vector3 InverseTransformPoint(Vector3 position) { }

	// RVA: 0x9FB450 Offset: 0x9F9C50 VA: 0x1809FB450
	public Transform get_root() { }

	// RVA: 0x9FB450 Offset: 0x9F9C50 VA: 0x1809FB450
	private Transform GetRoot() { }

	[NativeMethodAttribute] // RVA: 0x126A30 Offset: 0x125E30 VA: 0x180126A30
	// RVA: 0x9FC080 Offset: 0x9FA880 VA: 0x1809FC080
	public int get_childCount() { }

	// RVA: 0x9FBC60 Offset: 0x9FA460 VA: 0x1809FBC60
	public void SetAsFirstSibling() { }

	// RVA: 0x9FBD50 Offset: 0x9FA550 VA: 0x1809FBD50
	public void SetSiblingIndex(int index) { }

	[NativeMethodAttribute] // RVA: 0x126A60 Offset: 0x125E60 VA: 0x180126A60
	// RVA: 0x9FC590 Offset: 0x9FAD90 VA: 0x1809FC590
	public Vector3 get_lossyScale() { }

	[FreeFunctionAttribute] // RVA: 0x126A90 Offset: 0x125E90 VA: 0x180126A90
	// RVA: 0x9FB610 Offset: 0x9F9E10 VA: 0x1809FB610
	public bool IsChildOf(Transform parent) { }

	// RVA: 0x9FC9E0 Offset: 0x9FB1E0 VA: 0x1809FC9E0
	public void set_hasChanged(bool value) { }

	// RVA: 0x9FB3B0 Offset: 0x9F9BB0 VA: 0x1809FB3B0 Slot: 4
	public IEnumerator GetEnumerator() { }

	[FreeFunctionAttribute] // RVA: 0x126B00 Offset: 0x125F00 VA: 0x180126B00
	[NativeThrowsAttribute] // RVA: 0x126B00 Offset: 0x125F00 VA: 0x180126B00
	// RVA: 0x9FB370 Offset: 0x9F9B70 VA: 0x1809FB370
	public Transform GetChild(int index) { }

	// RVA: 0x9FC5E0 Offset: 0x9FADE0 VA: 0x1809FC5E0
	private void get_position_Injected(out Vector3 ret) { }

	// RVA: 0x9FCD50 Offset: 0x9FB550 VA: 0x1809FCD50
	private void set_position_Injected(ref Vector3 value) { }

	// RVA: 0x9FC2B0 Offset: 0x9FAAB0 VA: 0x1809FC2B0
	private void get_localPosition_Injected(out Vector3 ret) { }

	// RVA: 0x9FCAA0 Offset: 0x9FB2A0 VA: 0x1809FCAA0
	private void set_localPosition_Injected(ref Vector3 value) { }

	// RVA: 0x9FC750 Offset: 0x9FAF50 VA: 0x1809FC750
	private void get_rotation_Injected(out Quaternion ret) { }

	// RVA: 0x9FCDF0 Offset: 0x9FB5F0 VA: 0x1809FCDF0
	private void set_rotation_Injected(ref Quaternion value) { }

	// RVA: 0x9FC350 Offset: 0x9FAB50 VA: 0x1809FC350
	private void get_localRotation_Injected(out Quaternion ret) { }

	// RVA: 0x9FCB40 Offset: 0x9FB340 VA: 0x1809FCB40
	private void set_localRotation_Injected(ref Quaternion value) { }

	// RVA: 0x9FC3F0 Offset: 0x9FABF0 VA: 0x1809FC3F0
	private void get_localScale_Injected(out Vector3 ret) { }

	// RVA: 0x9FCBE0 Offset: 0x9FB3E0 VA: 0x1809FCBE0
	private void set_localScale_Injected(ref Vector3 value) { }

	// RVA: 0x9FC8C0 Offset: 0x9FB0C0 VA: 0x1809FC8C0
	private void get_worldToLocalMatrix_Injected(out Matrix4x4 ret) { }

	// RVA: 0x9FC490 Offset: 0x9FAC90 VA: 0x1809FC490
	private void get_localToWorldMatrix_Injected(out Matrix4x4 ret) { }

	// RVA: 0x9FB660 Offset: 0x9F9E60 VA: 0x1809FB660
	private void RotateAroundInternal_Injected(ref Vector3 axis, float angle) { }

	// RVA: 0x9FBD90 Offset: 0x9FA590 VA: 0x1809FBD90
	private void TransformDirection_Injected(ref Vector3 direction, out Vector3 ret) { }

	// RVA: 0x9FB490 Offset: 0x9F9C90 VA: 0x1809FB490
	private void InverseTransformDirection_Injected(ref Vector3 direction, out Vector3 ret) { }

	// RVA: 0x9FBE50 Offset: 0x9FA650 VA: 0x1809FBE50
	private void TransformPoint_Injected(ref Vector3 position, out Vector3 ret) { }

	// RVA: 0x9FB550 Offset: 0x9F9D50 VA: 0x1809FB550
	private void InverseTransformPoint_Injected(ref Vector3 position, out Vector3 ret) { }

	// RVA: 0x9FC540 Offset: 0x9FAD40 VA: 0x1809FC540
	private void get_lossyScale_Injected(out Vector3 ret) { }
}
```
