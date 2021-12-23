#include "InputManager.h"
bool InputManager::_currentKeyStates[256] = { false };
bool InputManager::_prevKeyStates[256] = { false };
POINT InputManager::_mousePosition = {};
HWND InputManager::_hWnd = {};
void InputManager::Init(HWND hWnd) noexcept
{
    _hWnd = hWnd;
}
void InputManager::Update() noexcept
{
    memcpy(_prevKeyStates, _currentKeyStates, sizeof(_currentKeyStates));
    for (size_t vkey = 0; vkey < 256; ++vkey)
    {
        if (GetAsyncKeyState(vkey) & 0x8000)
        {
            _currentKeyStates[vkey] = true;
        }
        else
        {
            _currentKeyStates[vkey] = false;
        }
    }
    GetCursorPos(&_mousePosition);
    ScreenToClient(_hWnd, &_mousePosition);
}
bool InputManager::GetButton(BYTE vkey) noexcept
{
    return (_currentKeyStates[vkey] && _prevKeyStates[vkey]);
}
bool InputManager::GetButtonDown(BYTE vkey) noexcept
{
    if (_prevKeyStates[vkey] == _currentKeyStates[vkey])
        return false;
    return _currentKeyStates[vkey];
}
bool InputManager::GetButtonUp(BYTE vkey) noexcept
{
    return (_currentKeyStates[vkey] == false && _prevKeyStates[vkey]);
}
POINT InputManager::GetMousePosition() noexcept
{
    return _mousePosition;
}