# IL2CPP Offset Finder Report

## MainMenu
- **Namespace**: Hyperstrange.WARPZ
- **Match Confidence**: 66.67%

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class MainMenu : Menu // TypeDefIndex: 7926
{
	// Fields
	private LevelId _lastLevel; // 0x50

	// Methods

	// RVA: 0x137C570 Offset: 0x137AD70 VA: 0x18137C570
	private void Awake() { }

	// RVA: 0x137C7A0 Offset: 0x137AFA0 VA: 0x18137C7A0
	private static voi
```

### Fields (1)
- `_lastLevel`: LevelId @ 0x50

### Methods (3)
- `Awake()`: void @ 0x137AD70
- `ShowGameCompletedPrompt()`: void @ 0x137AFA0
- `.ctor()`: void @ 0x136FD90

---

## CalendarData
- **Namespace**: System.Globalization
- **Match Confidence**: 100.00%

### Preview
```csharp
// Namespace: System.Globalization
internal class CalendarData // TypeDefIndex: 683
{
	// Fields
	internal const int MAX_CALENDARS = 23;
	internal string sNativeName; // 0x10
	internal string[] saShortDates; // 0x18
	internal string[] saYearMonths; // 0x20
	internal string[] saLongDates; // 0x28
	in
```

### Fields (20)
- `sNativeName`: string @ 0x10
- `saShortDates`: string[] @ 0x18
- `saYearMonths`: string[] @ 0x20
- `saLongDates`: string[] @ 0x28
- `sMonthDay`: string @ 0x30
- `saEraNames`: string[] @ 0x38
- `saAbbrevEraNames`: string[] @ 0x40
- `saAbbrevEnglishEraNames`: string[] @ 0x48
- `saDayNames`: string[] @ 0x50
- `saAbbrevDayNames`: string[] @ 0x58
- ... and 10 more

### Methods (9)
- `.ctor()`: void @ 0x5CB950
- `.cctor()`: void @ 0x5C9EB0
- `InitializeEraNames()`: void @ 0x5C9630
- `InitializeAbbreviatedEraNames()`: void @ 0x5C9140
- `GetCalendarData()`: CalendarData @ 0x5C8F40
- `CalendarIdToCultureName()`: string @ 0x5C8DB0
- `nativeGetTwoDigitYearMax()`: int @ 0x5CC180
- `nativeGetCalendarData()`: bool @ 0x5CC130
- `fill_calendar_data()`: bool @ 0x5CC120

---

## DebugUIHandlerButton
- **Namespace**: UnityEngine.Rendering.UI
- **Match Confidence**: 100.00%

### Preview
```csharp
// Namespace: UnityEngine.Rendering.UI
public class DebugUIHandlerButton : DebugUIHandlerWidget // TypeDefIndex: 4382
{
	// Fields
	public Text nameLabel; // 0x58
	private DebugUI.Button m_Field; // 0x60

	// Methods

	// RVA: 0xAAF360 Offset: 0xAADB60 VA: 0x180AAF360 Slot: 5
	internal override void
```

### Fields (2)
- `nameLabel`: Text @ 0x58
- `m_Field`: DebugUI.Button @ 0x60

### Methods (1)
- `.ctor()`: void @ 0x701790

---

## SceneManagerAPI
- **Namespace**: UnityEngine.SceneManagement
- **Match Confidence**: 100.00%

### Preview
```csharp
// Namespace: UnityEngine.SceneManagement
public class SceneManagerAPI // TypeDefIndex: 3301
{
	// Fields
	private static SceneManagerAPI s_DefaultAPI; // 0x0
	[CompilerGeneratedAttribute] // RVA: 0x127290 Offset: 0x126690 VA: 0x180127290
	[DebuggerBrowsableAttribute] // RVA: 0x127290 Offset: 0x1266
```

### Fields (2)
- `s_DefaultAPI`: SceneManagerAPI @ 0x0
- `<overrideAPI>k__BackingField`: SceneManagerAPI @ 0x8

### Methods (3)
- `get_ActiveAPI()`: SceneManagerAPI @ 0x80D370
- `get_overrideAPI()`: SceneManagerAPI @ 0x80D440
- `.cctor()`: void @ 0x80D310

---

## FMODRuntimeManagerOnGUIHelper
- **Namespace**: FMODUnity
- **Match Confidence**: 100.00%

### Preview
```csharp
// Namespace: FMODUnity
public class FMODRuntimeManagerOnGUIHelper : MonoBehaviour // TypeDefIndex: 6291
{
	// Fields
	public RuntimeManager TargetRuntimeManager; // 0x18

	// Methods

	// RVA: 0x37D9C0 Offset: 0x37C1C0 VA: 0x18037D9C0
	private void OnGUI() { }

	// RVA: 0x2D67D0 Offset: 0x2D4FD0 VA
```

### Fields (1)
- `TargetRuntimeManager`: RuntimeManager @ 0x18

### Methods (2)
- `OnGUI()`: void @ 0x37C1C0
- `.ctor()`: void @ 0x2D4FD0

---

## Player
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class Player : BaseBehaviour // TypeDefIndex: 7939
{
	// Fields
	public static Action<Player> OnStart; // 0x0
	public static Action<Player> OnFinish; // 0x8
	public static Action<Player> OnDeath; // 0x10
	public Action<PlayerWarpComponent> OnFinishWarpSuccess; // 0x40
	public Action<PlayerWarpComponent> OnButtonSuccess; // 0x48
	public Action<PlayerWarpCompo
```

### Fields (31)
- `OnStart`: Action<Player> @ 0x0
- `OnFinish`: Action<Player> @ 0x8
- `OnDeath`: Action<Player> @ 0x10
- `OnFinishWarpSuccess`: Action<PlayerWarpComponent> @ 0x40
- `OnButtonSuccess`: Action<PlayerWarpComponent> @ 0x48
- `OnWarpSuccess`: Action<PlayerWarpComponent> @ 0x50
- `OnWarpFail`: Action<PlayerWarpComponent> @ 0x58
- `OnWarpFinderUpdate`: Action<PlayerWarpComponent> @ 0x60
- `OnComboIncremented`: Action<PlayerComboComponent> @ 0x68
- `OnComboTimeOutUpdate`: Action<PlayerComboComponent> @ 0x70
- ... and 21 more

### Methods (28)
- `Awake()`: void @ 0x138C7C0
- `OnEnable()`: void @ 0x138CCD0
- `OnDisable()`: void @ 0x138CA00
- `OnLevelPrepareStart()`: void @ 0x138CFB0
- `OnLevelStart()`: void @ 0x138D0C0
- `OnLevelPrepareEnd()`: void @ 0x138CFA0
- `OnFinishWarp()`: void @ 0x138CFA0
- `get_Camera()`: Camera @ 0x2DA4F0
- `set_Camera()`: void @ 0x2DA9C0
- `get_CameraTransform()`: Transform @ 0x585F20
- ... and 18 more

---

## TimeManager
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class TimeManager : Singleton<TimeManager> // TypeDefIndex: 7986
{
	// Fields
	public static Action<float> OnTimeScaleChanged; // 0x0
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private static float <CurrentTimeScale>k__BackingField; // 0x8

	// Properties
	public static float CurrentTimeScale { get; set; }

	// Methods

	/
```

### Fields (2)
- `OnTimeScaleChanged`: Action<float> @ 0x0
- `<CurrentTimeScale>k__BackingField`: float @ 0x8

### Methods (5)
- `SetTimeScale()`: void @ 0x1345B80
- `get_CurrentTimeScale()`: float @ 0x1345DC0
- `set_CurrentTimeScale()`: void @ 0x1345E20
- `.ctor()`: void @ 0x1345D50
- `.cctor()`: void @ 0x1345C70

---

## FinishPanel
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class FinishPanel : Panel // TypeDefIndex: 7868
{
	// Methods

	// RVA: 0x1358770 Offset: 0x1356F70 VA: 0x181358770 Slot: 9
	public override void Hit(Player player) { }

	// RVA: 0x254B90 Offset: 0x253390 VA: 0x180254B90 Slot: 10
	public override void ResetState() { }

	// RVA: 0x1358810 Offset: 0x1357010 VA: 0x181358810
	public void .ctor() { }
}
```

### Methods (1)
- `.ctor()`: void @ 0x1357010

---

## PlayerMovementComponent
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class PlayerMovementComponent : ChildBehaviour<Player>, IUpdateListener, IFixedUpdateListener // TypeDefIndex: 7949
{
	// Fields
	[HeaderAttribute] // RVA: 0x212DA0 Offset: 0x2121A0 VA: 0x180212DA0
	[SerializeField] // RVA: 0x212DA0 Offset: 0x2121A0 VA: 0x180212DA0
	private float _minSpeed; // 0x48
	[SerializeField] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800
```

### Fields (17)
- `_minSpeed`: float @ 0x48
- `_deltaSpeed`: float @ 0x4C
- `_acceleration`: float @ 0x50
- `_breakDeltaSpeed`: float @ 0x54
- `_breakDeceleration`: float @ 0x58
- `_idleDeceleation`: float @ 0x5C
- `_idleDecelerationDelay`: float @ 0x60
- `_speedBeforeSlowMotion`: float @ 0x64
- `_currentAcceleration`: float @ 0x68
- `_idleDecelerate`: bool @ 0x6C
- ... and 7 more

### Methods (26)
- `OnEnable()`: void @ 0x1388710
- `OnDisable()`: void @ 0x1388330
- `OnFinish()`: void @ 0x1388AF0
- `OnRespawn()`: void @ 0x1388E00
- `OnWarpSuccess()`: void @ 0x1389010
- `HandleIdle()`: void @ 0x1387E30
- `OnWarpFail()`: void @ 0x1389000
- `OnBreak()`: void @ 0x1388320
- `DecreaseSpeed()`: void @ 0x1387D60
- `Accelerate()`: void @ 0x13879A0
- ... and 16 more

---

## PlayerWarpComponent
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class PlayerWarpComponent : ChildBehaviour<Player>, IUpdateListener // TypeDefIndex: 7957
{
	// Fields
	private RaycastHit _hitInfo; // 0x48
	private IHittable _currentHittable; // 0x78
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private float <CurrentWarpableDuration>k__BackingField; // 0x80
	[CompilerGeneratedAttribute] /
```

### Fields (4)
- `_hitInfo`: RaycastHit @ 0x48
- `_currentHittable`: IHittable @ 0x78
- `<CurrentWarpableDuration>k__BackingField`: float @ 0x80
- `<CurrentPanel>k__BackingField`: Panel @ 0x88

### Methods (11)
- `OnEnable()`: void @ 0x132E7C0
- `OnDisable()`: void @ 0x132E6B0
- `OnWarpDown()`: void @ 0x132EB30
- `HandleWarp()`: void @ 0x132E510
- `get_LastHitInfo()`: RaycastHit @ 0x132EBE0
- `get_WarpableFound()`: bool @ 0x132EC10
- `get_CurrentWarpableDuration()`: float @ 0x132EBD0
- `set_CurrentWarpableDuration()`: void @ 0x132EC60
- `get_CurrentPanel()`: Panel @ 0x3FA760
- `set_CurrentPanel()`: void @ 0x6583E0
- ... and 1 more

---

## PlayerComboComponent
- **Namespace**: Hyperstrange.WARPZ

### Preview
```csharp
// Namespace: Hyperstrange.WARPZ
public class PlayerComboComponent : ChildBehaviour<Player>, IUpdateListener // TypeDefIndex: 7945
{
	// Fields
	[SerializeField] // RVA: 0xC7370 Offset: 0xC6770 VA: 0x1800C7370
	private float _comboTimeout; // 0x48
	private bool _activeCombo; // 0x4C
	private float _lastComboIncrementTimeStamp; // 0x50
	[CompilerGeneratedAttribute] // RVA: 0xC7370 Offset: 0xC6770 V
```

### Fields (5)
- `_comboTimeout`: float @ 0x48
- `_activeCombo`: bool @ 0x4C
- `_lastComboIncrementTimeStamp`: float @ 0x50
- `<ComboTimeoutProgress>k__BackingField`: float @ 0x54
- `<ComboCount>k__BackingField`: int @ 0x58

### Methods (14)
- `OnEnable()`: void @ 0x1382F70
- `OnDisable()`: void @ 0x1382C60
- `OnRespawn()`: void @ 0x1383280
- `OnWarpSuccess()`: void @ 0x1383360
- `OnWarpFail()`: void @ 0x1382BD0
- `OnBreak()`: void @ 0x1382BD0
- `BreakCombo()`: void @ 0x1382BD0
- `IncrementCombo()`: void @ 0x1382BE0
- `get_ComboTimeout()`: float @ 0xDB1780
- `get_ComboTimeoutProgress()`: float @ 0x71D7F0
- ... and 4 more

---

