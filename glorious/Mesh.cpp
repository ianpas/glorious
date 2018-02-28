#include "stdafx.h"
#include "Mesh.h"
#include "MeshType.h"
#include "ITransform.h"

namespace Glorious
{
	Mesh::Mesh(IGameObject* game_object, std::string const& texture_path, std::string const& mesh_path)
		:Component(game_object)
	{

		auto const& device_manager{ DirectManager::GetSingleton() };
		auto& mesh_manager{ FbxManager::GetSingleton() };

		mesh_manager.ImportMesh(FileManager::GetExePath() + R"(\)" + mesh_path);

		auto fbx_mesh = mesh_manager.GetMesh();

		m_Material = fbx_mesh.m_Material;

		// TODO: temp
		/*auto transform = GetComponent<ITransform>();
		auto scale = transform->GetScale();
		float tile = scale.x;

		for (auto& each : fbx_mesh.m_Vertices)
		{
			each.m_Texture.x *= tile;
			each.m_Texture.y *= tile;
		}
		*/
		auto& vertices = fbx_mesh.m_Vertices;
		m_VertexAmount = vertices.size();

		D3D11_BUFFER_DESC vb_desc;
		std::memset(&vb_desc, 0, sizeof(vb_desc));
		vb_desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
		vb_desc.ByteWidth = sizeof(vertices[0])*vertices.size();
		vb_desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		/*auto& indices = fbx_mesh.m_Indices;
		m_IndexAmount = indices.size();

		D3D11_BUFFER_DESC ib_desc;
		std::memset(&ib_desc, 0, sizeof(ib_desc));
		ib_desc.Usage = D3D11_USAGE::D3D11_USAGE_IMMUTABLE;
		ib_desc.ByteWidth = sizeof(indices[0])*m_IndexAmount;
		ib_desc.BindFlags = D3D11_BIND_INDEX_BUFFER;*/

		try
		{
			m_VertexBuffer.Attach(device_manager.CreateBuffer(vb_desc, vertices.data()));
			if (texture_path != "")
			{
				auto path = FileManager::GetExePath() + R"(\)" + texture_path;
				m_Texture.Attach(device_manager.CreateShaderResourceView(std::wstring{ path.begin(),path.end() }));
			}
			//m_IndexBuffer.Attach(device_manager.CreateBuffer(ib_desc, indices.data()));
		}
		catch (std::exception const& e)
		{
			throw e;
		}

	}

	void Mesh::Update()
	{
		auto const& device_context{ GraphicsManager::GetSingleton().Get<GraphicsManager::DeviceContextType>() };

		UINT vb_stride{ sizeof(Type::Vertex) };
		UINT vb_offset{ 0 };

		device_context->IASetVertexBuffers(0, 1, m_VertexBuffer.GetAddressOf(), &vb_stride, &vb_offset);
		device_context->PSSetShaderResources(0, 1, m_Texture.GetAddressOf());

		//device_context->IASetIndexBuffer(m_IndexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
		device_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	int Mesh::GetIndexAmount() const
	{
		return m_IndexAmount;
	}

	int Mesh::GetVertexAmount() const
	{
		return m_VertexAmount;
	}

	Type::Material Mesh::GetMaterial() const
	{
		return m_Material;
	}
}
