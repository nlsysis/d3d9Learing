#include "CameraFol.h"
#include "input.h"
#include "airplane.h"
#include "debugproc.h"

CAMERA_tag m_camera;
float  g_moveSpeed = 0.0f;    //�ړ����x
float  g_rotationSpeed = 0.0f;   //��]���x
int	   g_ip_cnt = 0;  // ��ԏ�����

INTERPOLATION	g_ip[CAM_IP_MAX];		// ��ԗp���[�N (at/eye)

D3DXVECTOR3 move_tbl_at[] = {
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
	D3DXVECTOR3(100.0f, 0.0f, 0.0f),
	D3DXVECTOR3(100.0f, 0.0f, -100.0f),
	D3DXVECTOR3(0.0f, 0.0f, 0.0f),
};

D3DXVECTOR3 move_tbl_eye[] = {
	D3DXVECTOR3(0.0f, 50.0f, -100.0f),
	D3DXVECTOR3(0.0f, 50.0f, -10),
	D3DXVECTOR3(100.0f, 50.0f, -100.0f),
	D3DXVECTOR3(100.0f, 100.0f, -200.0f),
	D3DXVECTOR3(0.0f, 50.0f, -100.0f),
};

void InitCameraFol(LPDIRECT3DDEVICE9 pDevice)
{
	m_camera.pos = D3DXVECTOR3(0.0f, 40.0f, -150.0f);  // �J�����̏����ʒu
	m_camera.at = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_camera.up = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
	m_camera.rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	g_moveSpeed = 1.0f;
	g_rotationSpeed = D3DX_PI * 0.01f;

	// ���_�ƒ����_�̋������v�Z
	float vx, vz;
	vx = m_camera.pos.x - m_camera.at.x;
	vz = m_camera.pos.z - m_camera.at.z;
	m_camera.len = sqrtf(vx * vx + vz * vz);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&m_camera.mtxProjection);

	D3DXMatrixPerspectiveFovLH(
		&m_camera.mtxProjection,
		D3DX_PI / 4,   //���W�A���p�ŉ�p�w��
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,
		0.1f,
		1000.0f);
	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &m_camera.mtxProjection);
	m_camera.at = GetAirplanePos();
}

void UpdateCameraFol(LPDIRECT3DDEVICE9 pDevice)
{
	Keyboard_Update();
	if (g_ip_cnt <= 0)
	{

		if (Keyboard_IsPress(DIK_Z))
		{// ���_����u���v
			m_camera.rot.y += g_rotationSpeed;
			if (m_camera.rot.y > D3DX_PI)
			{
				m_camera.rot.y -= D3DX_PI * 2.0f;
			}

			m_camera.pos.x = m_camera.at.x - sinf(m_camera.rot.y) * m_camera.len;
			m_camera.pos.z = m_camera.at.z - cosf(m_camera.rot.y) * m_camera.len;
		}

		if (Keyboard_IsPress(DIK_C))
		{// ���_����u�E�v
			m_camera.rot.y -= g_rotationSpeed;
			if (m_camera.rot.y < -D3DX_PI)
			{
				m_camera.rot.y += D3DX_PI * 2.0f;
			}

			m_camera.pos.x = m_camera.at.x - sinf(m_camera.rot.y) * m_camera.len;
			m_camera.pos.z = m_camera.at.z - cosf(m_camera.rot.y) * m_camera.len;
		}

		if (Keyboard_IsPress(DIK_Y))
		{// ���_�ړ��u��v
			m_camera.pos.y += g_moveSpeed;
		}

		if (Keyboard_IsPress(DIK_N))
		{// ���_�ړ��u���v
			m_camera.pos.y -= g_moveSpeed;
		}

		if (Keyboard_IsPress(DIK_Q))
		{// �����_����u���v
			m_camera.rot.y -= g_rotationSpeed;
			if (m_camera.rot.y < -D3DX_PI)
			{
				m_camera.rot.y += D3DX_PI * 2.0f;
			}

			m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
			m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
		}

		if (Keyboard_IsPress(DIK_E))
		{// �����_����u�E�v
			m_camera.rot.y += g_rotationSpeed;
			if (m_camera.rot.y > D3DX_PI)
			{
				m_camera.rot.y -= D3DX_PI * 2.0f;
			}

			m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
			m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
		}

		if (Keyboard_IsPress(DIK_T))
		{// �����_�ړ��u��v
			m_camera.at.y += g_moveSpeed;
		}

		if (Keyboard_IsPress(DIK_B))
		{// �����_�ړ��u���v
			m_camera.at.y -= g_moveSpeed;
		}

		if (Keyboard_IsPress(DIK_U))
		{// �߂Â�
			m_camera.len -= g_moveSpeed;
		}

		if (Keyboard_IsPress(DIK_M))
		{// �����
			m_camera.len += g_moveSpeed;
		}

		// �����J���������J�n�H
		if (Keyboard_IsTrigger(DIK_9))
		{
			memset(&g_ip[0], 0, sizeof(INTERPOLATION));
			memset(&g_ip[1], 0, sizeof(INTERPOLATION));

			g_ip[0].dt = 0.01f;
			g_ip[0].tbl = move_tbl_at;
			g_ip[0].tbl_cnt = sizeof(move_tbl_at) / sizeof(D3DXVECTOR3);
			g_ip[0].use = true;
			g_ip_cnt++;

			g_ip[1].dt = 0.01f;
			g_ip[1].tbl = move_tbl_eye;
			g_ip[1].tbl_cnt = sizeof(move_tbl_eye) / sizeof(D3DXVECTOR3);
			g_ip[1].use = true;
			g_ip_cnt++;
		}

		// �J�����������ɖ߂�
		if (Keyboard_IsPress(DIK_R))
		{
			UninitCameraFol();
			InitCameraFol(pDevice);
		}

		PrintDebugProc("*** ���_���� ***\n");
		PrintDebugProc("��ړ� : Y\n");
		PrintDebugProc("���ړ� : N\n");
		PrintDebugProc("������ : Z\n");
		PrintDebugProc("�E���� : C\n");
		PrintDebugProc("�߂Â� : U\n");
		PrintDebugProc("����� : M\n");
		PrintDebugProc("\n");

		PrintDebugProc("*** �����_���� ***\n");
		PrintDebugProc("��ړ� : T\n");
		PrintDebugProc("���ړ� : B\n");
		PrintDebugProc("������ : Q\n");
		PrintDebugProc("�E���� : E\n");
		PrintDebugProc("\n");

		PrintDebugProc("*** �v���C���[���� ***\n");
		PrintDebugProc("BULLET : SPACE\n");
	}
	

	D3DXMatrixIdentity(&m_camera.mtxView);
	D3DXMatrixLookAtLH(&m_camera.mtxView,
		&m_camera.pos,		// �J�����̎��_(�ʒu)
		&m_camera.at,		// �J�����̒����_
		&m_camera.up);

	pDevice->SetTransform(D3DTS_VIEW, &m_camera.mtxView);
}

D3DXVECTOR3 GetCameraFolPosition()
{
	return m_camera.pos;
}

D3DXMATRIX GetFolViewMatrix()
{
	return m_camera.mtxView;
}

void SetLookat(D3DXVECTOR3 atPos)
{
	m_camera.at.x = atPos.x;
	m_camera.at.z = atPos.z;
}

CAMERA* GetCameraFol()
{
	return &m_camera;
}

int GetIPCnt(void)
{
	return g_ip_cnt;
}

void UninitCameraFol()
{
	g_ip_cnt = 0;
}