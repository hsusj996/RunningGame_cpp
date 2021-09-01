#include "CPlayer.h"
#include "Stage.h"

CPlayer::CPlayer()
{
}

CPlayer::~CPlayer()
{
}

bool CPlayer::Init()
{
    m_iX = 0;
    m_iY = 8;
    m_bJump = false;
    m_iJumpPower = 2;
    m_eJumpState = JS_STOP;
    return true;
}

void CPlayer::Update(CStage cStage)
{

    //키입력을 받는다.
    //GetAsyncKeyState는 Win32 API의 키입력 함수
    //즉시 반응한다. 눌렀을 때 true를 반환
    if (GetAsyncKeyState('A') & 0x8000) {
        m_iX--;

        if (m_iX < 0)
            m_iX = 0;
    }
    if (GetAsyncKeyState('D') & 0x8000) {
        m_iX++;

        if (m_iX >= 50)
            m_iX = 49;
    }
    if (GetAsyncKeyState(VK_SPACE) & 0x8000 && !m_bJump) {
        m_bJump = true;
        m_iJumpCount = 0;
        m_eJumpState = JS_UP;
    }



    if (m_bJump) {
        switch (m_eJumpState) {
        case JS_UP:
            m_iJumpCount++;
            if (m_iJumpCount > JUMP_BLOCK_MAX) {
                m_iJumpCount = JUMP_BLOCK_MAX;
                m_eJumpState = JS_DOWN;
            }
            else
                m_iY--;
            break;
        case JS_DOWN:
            m_iJumpCount--;
            if (m_iJumpCount < 0) {
                m_iJumpCount = 0;
                m_eJumpState = JS_STOP;
            }
            else {
                m_iY++;
            }
            break;
        case JS_STOP:
            m_bJump = false;
            break;
        }
    }
}
