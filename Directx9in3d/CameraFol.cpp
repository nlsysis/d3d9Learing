#include "CameraFol.h"
#include "input.h"
#include "airplane.h"

CAMERA_tag m_camera;
float  g_moveSpeed = 0.0f;    //�ړ����x
float  g_rotationSpeed = 0.0f;   //��]���x

void InitCameraFol(LPDIRECT3DDEVICE9 pDevice)
{
	m_camera.pos = D3DXVECTOR3(0.0f, 40.0f, -120.0f);  // �J�����̏����ʒu
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
	if (Keyboard_IsPress(DIK_A))
	{
		if (Keyboard_IsPress(DIK_W))
		{// ���O�ړ�
			m_camera.pos.x -= cosf(m_camera.rot.y + D3DX_PI * 0.25f) * g_moveSpeed;
			m_camera.pos.z += sinf(m_camera.rot.y + D3DX_PI * 0.25f) * g_moveSpeed;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// ����ړ�
			m_camera.pos.x -= cosf(m_camera.rot.y - D3DX_PI * 0.25f) * g_moveSpeed;
			m_camera.pos.z += sinf(m_camera.rot.y - D3DX_PI * 0.25f) * g_moveSpeed;
		}
		else
		{// ���ړ�
			m_camera.pos.x -= cosf(m_camera.rot.y) * g_moveSpeed;
			m_camera.pos.z += sinf(m_camera.rot.y) * g_moveSpeed;
		}

		m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
		m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
	}
	else if (Keyboard_IsPress(DIK_D))
	{
		if (Keyboard_IsPress(DIK_W))
		{// �E�O�ړ�
			m_camera.pos.x += cosf(m_camera.rot.y - D3DX_PI * 0.25f) * g_moveSpeed;
			m_camera.pos.z -= sinf(m_camera.rot.y - D3DX_PI * 0.25f) * g_moveSpeed;
		}
		else if (Keyboard_IsPress(DIK_S))
		{// �E��ړ�
			m_camera.pos.x += cosf(m_camera.rot.y + D3DX_PI * 0.25f) * g_moveSpeed;
			m_camera.pos.z -= sinf(m_camera.rot.y + D3DX_PI * 0.25f) * g_moveSpeed;
		}
		else
		{// �E�ړ�
			m_camera.pos.x += cosf(m_camera.rot.y) * g_moveSpeed;
			m_camera.pos.z -= sinf(m_camera.rot.y) * g_moveSpeed;
		}

		m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
		m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
	}
	else if (Keyboard_IsPress(DIK_W))
	{// �O�ړ�
		m_camera.pos.x += sinf(m_camera.rot.y) * g_moveSpeed;
		m_camera.pos.z += cosf(m_camera.rot.y) * g_moveSpeed;

		m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
		m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
	}
	else if (Keyboard_IsPress(DIK_S))
	{// ��ړ�
		m_camera.pos.x -= sinf(m_camera.rot.y) * g_moveSpeed;
		m_camera.pos.z -= cosf(m_camera.rot.y) * g_moveSpeed;

		m_camera.at.x = m_camera.pos.x + sinf(m_camera.rot.y) * m_camera.len;
		m_camera.at.z = m_camera.pos.z + cosf(m_camera.rot.y) * m_camera.len;
	}

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