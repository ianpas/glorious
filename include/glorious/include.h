#pragma once

#include <functional>
#include <memory>
#include <mutex>
#include <chrono>
#include <vector>
#include <string>
#include <algorithm>
#include <unordered_map>

//
#include <wrl.h>

#include <d3d11.h>
#include <dxgi.h>

#include <DirectXMath.h>

#pragma comment ( lib, "d3d11" )
#pragma comment ( lib, "dxgi" )

//
#pragma comment ( lib, "DirectXTex.lib" )

//
#pragma comment ( lib, "BulletCollision.lib" )
#pragma comment ( lib, "BulletDynamics.lib" )
#pragma comment ( lib, "LinearMath.lib" )

#include "..\bullet\btBulletDynamicsCommon.h"
#include "BulletManager.h"

//
#include "..\mesh-get\include.h"

#pragma comment ( lib, "glorious.lib" )
#include "Time.h"
#include "Debug.h"
#include "Input.h"
#include "Math.h"

#include "DirectManager.h"
#include "GraphicsManager.h"
#include "FileManager.h"

#include "GameObject.h"
#include "Component.h"
#include "Transform.h"
#include "Camera.h"
#include "Renderer.h"
#include "PixelShader.h"
#include "VertexShader.h"
#include "Rigidbody.h"
#include "Light.h"

#include "Mesh.h"



