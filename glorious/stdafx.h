#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include <functional>
#include <memory>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

#include <wrl.h>

#include <d3d11.h>
#include <dxgi.h>

#include <DirectXMath.h>

#pragma comment ( lib, "d3d11" )
#pragma comment ( lib, "dxgi" )

#include "Debug.h"
#include "Input.h"
#include "Time.h"
#include "Math.h"

#include "DirectManager.h"
#include "GraphicsManager.h"
#include "..\include\mesh-get\include.h"

#include "..\include\bullet\btBulletDynamicsCommon.h"
#include "BulletManager.h"
#include "FileManager.h"

