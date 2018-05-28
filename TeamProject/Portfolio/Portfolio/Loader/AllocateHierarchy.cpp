#include "../stdafx.h"
#include "AllocateHierarchy.h"


// ������ ���� : ���� �޸𸮸� �Ҵ��ؼ� �������� �����ϰ� ppNewFrame ���ڿ� ����
// ������ �������� �̸��� �𵨸� ���α׷����� ������ �������� �̸��� ���ڷ� �޾� ����
// ������ ��ü�� Ʈ�������� �ٹ̱� ���� �غ� �۾�
STDMETHODIMP AllocateHierarchy::CreateFrame(THIS_ LPCSTR Name, LPD3DXFRAME *ppNewFrame)
{
	FRAME_EX* pFrameEx = new FRAME_EX;
	
	// TODO : �̸��� �� �������ּ���. ���� ������.
	if (Name != NULL)
	{
		pFrameEx->Name = new char[strlen(Name) + 1];
		strcpy_s(pFrameEx->Name, (strlen(Name) + 1), Name);
	}
	else
	{
		pFrameEx->Name = NULL;
	}

	D3DXMatrixIdentity(&pFrameEx->TransformationMatrix);
	D3DXMatrixIdentity(&pFrameEx->CombinedTM);

	pFrameEx->pMeshContainer = NULL;
	pFrameEx->pFrameFirstChild = NULL;
	pFrameEx->pFrameSibling = NULL;

	// ������ �����͸� ��������!
	*ppNewFrame = pFrameEx;
	
	

	return S_OK;
}


// �Ž� �����̳� ���� : ���� �޸𸮸� �Ҵ��ؼ��������� �����ϰ� ppNewMeshContainer ���ڿ� ����
// �Ž��� �̸�, ��Ƽ����, �ؽ�ó�� ����
// ������ �Ž� �����̳ʿ� pSkinInfo �� ����
// Skinning �� ���� �غ� �۾� - Base�� �Ѱ��شٴ� ��!
STDMETHODIMP AllocateHierarchy::CreateMeshContainer(
	THIS_ LPCSTR Name,
	CONST D3DXMESHDATA *pMeshData,
	CONST D3DXMATERIAL *pMaterials,
	CONST D3DXEFFECTINSTANCE *pEffectInstances,
	DWORD NumMaterials,
	CONST DWORD *pAdjacency,
	LPD3DXSKININFO pSkinInfo,
	LPD3DXMESHCONTAINER *ppNewMeshContainer)
{
	MESHCONTAINER_EX* pMeshContainerEx = NULL;
	LPD3DXMESH pMesh = NULL;

	if (pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		assert(false && _T("D3DXMESHTYPE_MESH Ÿ�Ը� ��� ����"));
	}

	pMesh = pMeshData->pMesh;

	if (pMesh->GetFVF() == 0)
	{
		assert(false && _T("FVF Flag �� �������� ����"));
	}

	pMeshContainerEx = new MESHCONTAINER_EX;
	memset(pMeshContainerEx, 0, sizeof(MESHCONTAINER_EX));
	
	// �̸��� �־���
	if (Name != NULL)
	{
		pMeshContainerEx->Name = new char[strlen(Name) + 1];
		strcpy_s(pMeshContainerEx->Name, (strlen(Name) + 1), Name);
	}
	
	// if no normals are in the mesh, add them
	// ����� �� ������ �����ٰ� ���ٸ� �Ƹ� �� if���� ������ ���� �������̴�
	if ((pMesh->GetFVF() & D3DFVF_NORMAL) == false)
	{
		pMesh->CloneMeshFVF(pMesh->GetOptions(),
			pMesh->GetFVF() | D3DFVF_NORMAL, g_pDevice, &pMesh);

		// �븻 ���� ���Բ� �����
		D3DXComputeNormals(pMesh, NULL);
	}

	pMesh->AddRef();
	pMeshContainerEx->pOrigMesh = pMesh;

	// CloneMesh�� �����ؼ� WorkMesh�� �־���
	pMeshContainerEx->pOrigMesh->CloneMeshFVF(
		pMeshContainerEx->pOrigMesh->GetOptions(),
		pMeshContainerEx->pOrigMesh->GetFVF(),
		g_pDevice,
		&pMeshContainerEx->pWorkMesh);

	for (DWORD i = 0; i < NumMaterials; ++i)
	{
		MTLTEX* pMtlTex = new MTLTEX;
		pMtlTex->SetMaterial(pMaterials[i].MatD3D);
		pMtlTex->SetTexture(g_pTextureManager->GetTexture(m_path + pMaterials[i].pTextureFilename));
		pMeshContainerEx->vecMtlTex.push_back(pMtlTex);
	}

	// pSkinInfo �� ������ ����
	if (pSkinInfo != NULL)
	{
		pMeshContainerEx->pSkinInfo = pSkinInfo;
		(pSkinInfo)->AddRef();

		// pSkinInfo->GetNumBones() : �� �Ž��� ������ �ִ� ��(������)�� ����
		DWORD numBones = pSkinInfo->GetNumBones();
		pMeshContainerEx->ppBoneMatrixPtrs = new D3DXMATRIX*[numBones];
		pMeshContainerEx->pBoneOffsetMatrices = new D3DXMATRIX[numBones];
		pMeshContainerEx->pFinalBoneMatrices = new D3DXMATRIX[numBones];

		// �� �������� ������ �޽������̳��� ������ �ѱ�
		for (DWORD i = 0; i < numBones; ++i)
		{
			pMeshContainerEx->pBoneOffsetMatrices[i] = *(pSkinInfo->GetBoneOffsetMatrix(i));
		}
	}

	*ppNewMeshContainer = pMeshContainerEx;
	
	return S_OK;
}


//�����ߴ� �������� ����
//������ ���� �Ҵ� ����� �κ��� ��� ����
STDMETHODIMP AllocateHierarchy::DestroyFrame(THIS_ LPD3DXFRAME pFrameToFree)
{
	SAFE_DELETE_ARRAY(pFrameToFree->Name);
	SAFE_DELETE(pFrameToFree);

	return S_OK;
}


//�����ߴ� �Ž� �����̳ʸ� ����
//������ ���� �Ҵ� ����� �κ��� ��� ����
STDMETHODIMP AllocateHierarchy::DestroyMeshContainer(THIS_ LPD3DXMESHCONTAINER pMeshContainerToFree)
{
	MESHCONTAINER_EX* pMeshContainerEx = (MESHCONTAINER_EX*)pMeshContainerToFree;
	if (pMeshContainerEx == NULL)
		return E_FAIL;

	SAFE_DELETE_ARRAY(pMeshContainerEx->Name);
	SAFE_RELEASE(pMeshContainerEx->pOrigMesh);
	SAFE_RELEASE(pMeshContainerEx->pWorkMesh);

	for (auto p : pMeshContainerEx->vecMtlTex)
	{
		SAFE_RELEASE(p);
	}

	SAFE_DELETE_ARRAY(pMeshContainerEx->ppBoneMatrixPtrs);
	SAFE_DELETE_ARRAY(pMeshContainerEx->pBoneOffsetMatrices);
	SAFE_DELETE_ARRAY(pMeshContainerEx->pFinalBoneMatrices);

	SAFE_RELEASE(pMeshContainerEx->pSkinInfo);

	return S_OK;
}