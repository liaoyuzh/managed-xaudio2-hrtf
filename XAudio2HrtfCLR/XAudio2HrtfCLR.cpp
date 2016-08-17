#include "XAudio2HrtfCLR.h"

namespace XAudio2Hrtf
{
	PositionalSound::PositionalSound(System::String ^filename)
	{
		_nativeObj = new XAudio2HrtfNative();

		pin_ptr<const wchar_t> transformedFileName = PtrToStringChars(filename);

		int returned = _nativeObj->LoadFile(transformedFileName);
		
		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}

		returned = _nativeObj->Initialize();

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	PositionalSound::PositionalSound(System::String ^filename, HrtfEnvironment environment) : PositionalSound(filename)
	{
		switch (environment)
		{
			case(HrtfEnvironment::Large):
				this->_nativeObj->SetEnvironment((int)environment);
				break;

		}
	}

	void PositionalSound::Play()
	{
		int returned = _nativeObj->Play();

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	void PositionalSound::SetEnvironment(HrtfEnvironment environment)
	{
		int returned = _nativeObj->SetEnvironment((int)environment);
	}

	void PositionalSound::Stop()
	{
		int returned = _nativeObj->Stop();

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	void PositionalSound::SetVolume(float value)
	{
		int returned = _nativeObj->SetVolume(value);

		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}

	void PositionalSound::SetPosition(float x, float y, float z)
	{
		this->_x = x;
		this->_y = y;
		this->_z = z;

		int returned = _nativeObj->SetPosition(this->_x, this->_y, this->_z);
		
		if (returned != 0) {
			throw gcnew System::Exception(returned.ToString());
		}
	}
}
