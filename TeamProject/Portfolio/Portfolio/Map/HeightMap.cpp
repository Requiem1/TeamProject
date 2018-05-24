#include "../stdafx.h"
#include "HeightMap.h"
//#include "Ray.h"

HeightMap::HeightMap()
{
	m_pMesh = NULL;
	m_pMtlTex = NULL;
}


HeightMap::~HeightMap()
{
	SAFE_RELEASE(m_pMesh);
	SAFE_RELEASE(m_pMtlTex);
}

void HeightMap::Load(const char * fullPath, D3DXMATRIXA16 * pMat)
{
	vector<VERTEX_PNT> vecVertex;
	vecVertex.resize(m_dimension * m_dimension);
	m_vecVertex.resize(m_dimension * m_dimension);

	// raw ������ �ҷ��´�
	std::ifstream fin(fullPath, std::ios::binary);

	// raw���Ͽ��� �� ��ġ�� ����(y)���� ����ִ�!
	// 2���� �迭�� 1���� ��ġ ����(x���� 1��, x�� ���� �� ������ z�� 1�ö�)�̹Ƿ�
	// z( x( input ) ) ���·� �Է¹޴´�
	for (int z = 0; z < m_dimension; z++)
	{
		for (int x = 0; x < m_dimension; x++)
		{
			int index = z * m_dimension + x;
			int y = fin.get();
			
			vecVertex[index].p = D3DXVECTOR3(x, y, z);
			vecVertex[index].n = D3DXVECTOR3(0, 1, 0);
			vecVertex[index].t = D3DXVECTOR2( x / (float)m_numTile,  1 - (z / (float)m_numTile) );	
			// ����ü �ؽ��İ� 0,0���� m_numTile, m_numTile ������� ġ��
			// ������ �ؽ����� ��ġ�� x�� z�� ������ �Ÿ����̹Ƿ�
			// �� x / m_numTile, 1 - z / m_numTile �̴�!

			// pMat�� �ִٸ� �׸�ŭ �̵����ش�!
			if (pMat != NULL)
			{
				D3DXVec3TransformCoord(&vecVertex[index].p,	&vecVertex[index].p, pMat);
			}

			// ĳ���Ͱ� �������� ������ �� �ֵ��� ���̸� ����ϱ� ���� �޴´�
			m_vecVertex[index] = vecVertex[index].p;
		}
	}

	fin.close();

	// ũ��� pMat����!
	if (pMat != NULL)
	{
		m_scale.x = pMat->_11;	// ���� ��ġ x
		m_scale.z = pMat->_33;	// ���� ��ġ z
	}

	m_size.x = m_numTile * m_scale.x;
	m_size.z = m_numTile * m_scale.z;

	// �� Ÿ��(2���� �ﰢ��) ����
	// �ε��� ���۷�!
	vector<DWORD> vecIndex;
	vecIndex.reserve(m_numTile * m_numTile * 3 * 2);

	// set index
	for (int z = 0; z < m_numTile; z++)
	{
		for (int x = 0; x < m_numTile; x++)
		{
			// 1--3
			// 0--2
			int _0 = (z + 0) * m_dimension + x + 0;
			int _1 = (z + 1) * m_dimension + x + 0;
			int _2 = (z + 0) * m_dimension + x + 1;
			int _3 = (z + 1) * m_dimension + x + 1;

			// �� Ÿ�Ͽ� �־��� �ε��� push-back
			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);
		}
	}


	// set normal
	for (int z = 1; z < m_numTile; z++)
	{
		for (int x = 1; x < m_numTile; x++)
		{
			//--u--
			//l-n-r
			//--d--
			int index = z * m_dimension + x;

			int l = index - 1;
			int r = index + 1;
			int u = index + m_dimension;
			int d = index - m_dimension;

			// n�� �븻���� up-down left-right �� �̷���� ���� ���� ����
			D3DXVECTOR3 du = m_vecVertex[u] - m_vecVertex[d];
			D3DXVECTOR3 lr = m_vecVertex[r] - m_vecVertex[l];
			D3DXVECTOR3 n;

			D3DXVec3Cross(&n, &du, &lr);
			D3DXVec3Normalize(&n, &n);

			vecVertex[index].n = n;
		}
	}

	// �ε����� 16��Ʈ�� �ƴ϶� 32��Ʈ�̴� (������ 257 * 257 -> 2����Ʈ �̻��̹Ƿ�)
	// D3DXMESH_32BIT�� ���̸� �ȴ�
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), 
		D3DXMESH_MANAGED | D3DXMESH_32BIT, VERTEX_PNT::FVF,	g_pDevice, &m_pMesh);

	// ���ؽ� ����
	VERTEX_PNT* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(VERTEX_PNT));
	m_pMesh->UnlockVertexBuffer();

	// �ε��� ����
	DWORD* pI = NULL;
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));	// �ﰢ�� �� �ϳ��ϱ� size / 3
	m_pMesh->UnlockIndexBuffer();

	// ��Ʈ����Ʈ
	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));
	m_pMesh->UnlockAttributeBuffer();

	// �������� ����
	// �ﰢ�� �� 3�� -> ���� 3���̹Ƿ� ���ϱ� 3
	vector<DWORD> vecAdjBuffer(m_pMesh->GetNumFaces() * 3);
	m_pMesh->GenerateAdjacency(FLT_EPSILON, &vecAdjBuffer[0]);

	// �޽��� �� �� ������ ���� ������ ������, �����ս��� ����ȭ�Ѵ�.
	// D3DXMESHOPT_ATTRSORT -> ��Ʈ����Ʈ�� �ϳ��̹Ƿ� ���� �ʿ� X
	m_pMesh->OptimizeInplace(D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdjBuffer[0], 0, 0, 0);
}

void HeightMap::SetMtlTex(D3DMATERIAL9 & mtl, LPDIRECT3DTEXTURE9 pTex)
{
	m_pMtlTex = new MTLTEX;
	m_pMtlTex->SetMaterial(mtl);
	m_pMtlTex->SetTexture(pTex);
}

void HeightMap::Init()
{
	SetSurface();
}

void HeightMap::Update()
{
}

void HeightMap::Render()
{
	g_pDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	g_pDevice->SetMaterial(&m_pMtlTex->GetMaterial());
	g_pDevice->SetTexture(0, m_pMtlTex->GetTexture());
	m_pMesh->DrawSubset(0);
	g_pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

	//g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecObstacleVertex.size() / 3, &m_vecObstacleVertex[0], sizeof(D3DXVECTOR3));
	//g_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	g_pDevice->SetRenderState(D3DRS_FOGENABLE, false);
}

bool HeightMap::GetHeight(OUT float & height, const D3DXVECTOR3 & pos)
{
	if (pos.x < 0 || pos.z < 0 || pos.x > m_size.x || pos.z > m_size.z)
	{
		height = 0;
		return false;
	}

	// �Ҽ����� �� ���� ��ġ
	int nX = (int)(pos.x / m_scale.x);
	int nZ = (int)(pos.z / m_scale.z);

	// ���� ĭ���� �̵��� ��ġ��
	float deltaX = (pos.x / m_scale.x) - nX;
	float deltaZ = (pos.z / m_scale.z) - nZ;

	int index0 = (nZ + 0) * m_dimension + (nX + 0);
	int index1 = (nZ + 1) * m_dimension + (nX + 0);
	int index2 = (nZ + 0) * m_dimension + (nX + 1);
	int index3 = (nZ + 1) * m_dimension + (nX + 1);

	// x + y = 1�� ������ �������� �̿��϶�( y = -x + 1 )
	// 1-3 
	// |/|
	// 0-2
	// x + y < 1�̸� 012, x + y >= 1�̸� 123
	if (deltaX + deltaZ < 1.0f)
	{
		// 012 �ﰢ�� ���
		float zY = m_vecVertex[index1].y - m_vecVertex[index0].y;
		float xY = m_vecVertex[index2].y - m_vecVertex[index0].y;

		height = m_vecVertex[index0].y + (zY * deltaZ) + (xY * deltaX);
	}
	else
	{
		deltaX = 1 - deltaX;
		deltaZ = 1 - deltaZ;

		// 123 �ﰢ�� ���
		float zY = m_vecVertex[index1].y - m_vecVertex[index3].y;
		float xY = m_vecVertex[index2].y - m_vecVertex[index3].y;

		height = m_vecVertex[index3].y + (zY * deltaZ) + (xY * deltaX);
	}

	return true;
}

bool HeightMap::CalcPickedPosition(D3DXVECTOR3 & vOut, WORD screenX, WORD screenY)
{
	// ���忡 �� ���� ������ ���߿� �� ���� �����Ƿ� �ּ�ó����
	// 
	// ��ǥ�� ���� �� world��ǥ�� �ű� �� -> ray�� ����
	// �� ray�� ���� �̿��ؼ� vector�� �����ǿ��� ���� �Ÿ��� ª�� �ָ� ã�Ƽ�
	// WndProc�� �Ѱ��༭ ĳ���Ͱ� �� pos�� �� �� �ְ� �Ѵ�
	//Ray r = Ray::RayAtWorldSpace(screenX, screenY);

	//float intersectDist;
	//float minDistance = FLT_MAX;

	//bool isInterect = false;

	//for (size_t i = 0; i < m_vecSurfaceVertex.size(); i += 3)
	//{
	//	if (r.CalcIntersectTri(&m_vecSurfaceVertex[i], &intersectDist))
	//	{
	//		if (intersectDist < minDistance)
	//		{
	//			minDistance = intersectDist;
	//			isInterect = true;

	//			// Ŭ���� ��ġ(m_pos)���� �ٴ��� ����(m_dir) * �Ÿ�(intersectDist)�� ������
	//			vOut = r.m_pos + (r.m_dir * intersectDist);
	//		}
	//	}
	//}

	//return isInterect;
	return false;
}

void HeightMap::SetSurface()
{
	// Ÿ�ϸ� ����� �ſ� �Ȱ��� �۾��� �Ѵ�
	vector<D3DXVECTOR3> vecPos;
	vector<DWORD> vecIndex;

	int surfaceDim = 5;
	int numSurfaceTile = surfaceDim - 1;

	vecPos.reserve(surfaceDim * surfaceDim);

	for (size_t z = 0; z < surfaceDim; z++)
	{
		for (size_t x = 0; x < surfaceDim; x++)
		{
			// ������ index�� x z ���� m_numTile(5)�� ���� 5 * 5�� vertex�� �����ϰ� �Ѵ�
			DWORD index = ((z / (float)numSurfaceTile) * m_dimension) * m_numTile +
				(x / (float)numSurfaceTile) * m_numTile;

			vecPos.push_back(m_vecVertex[index]);
		}
	}

	// �� ��(Surface)�� �ΰ��� �ﰢ��(3���� ��) �ʿ� -> 2 * 3
	// Surface�� 5 * 5�� �ʿ��ϹǷ� 5 * 5 * 2 * 3���� �ʿ��ϴ�
	vecIndex.reserve(numSurfaceTile * numSurfaceTile * 2 * 3);

	// ��(Surface)�� �����!
	for (size_t z = 0; z < numSurfaceTile; z++)
	{
		for (size_t x = 0; x < numSurfaceTile; x++)
		{
			DWORD _0 = (z + 0) * surfaceDim + (x + 0);
			DWORD _1 = (z + 1) * surfaceDim + (x + 0);
			DWORD _2 = (z + 0) * surfaceDim + (x + 1);
			DWORD _3 = (z + 1) * surfaceDim + (x + 1);

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_2);

			vecIndex.push_back(_2);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);
		}
	}

	// 5 * 5 ũ���� Surface���� ����
	for (size_t i = 0; i < vecIndex.size(); i++)
	{
		m_vecSurfaceVertex.push_back(vecPos[vecIndex[i]]);
	}
}


void HeightMap::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	//case WM_RBUTTONUP:
	{
		//D3DXVECTOR3 pos;
		//if (CalcPickedPosition(pos, SCREEN_POINT(lParam)) == true)
		//{
		//	float num;
		//	GetHeight(num, pos);
		//	pos.y = num;
		//	// ĳ���͸� pos�� �̵��ϰ� �ϱ�
		//	//m_charPos = pos;
		//	static_cast<IDisplayObject*>(g_pPlayerMGR->GetPlayer(1).SetDestination(pos));
		//}
	}
	}
}
