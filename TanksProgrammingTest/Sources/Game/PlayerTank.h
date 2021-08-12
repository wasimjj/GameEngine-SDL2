#pragma once
#include "TextureComponent.h"
#include <iostream>


class PlayerTank 
{

public:
	PlayerTank();
   ~PlayerTank();

	TextureComponent* TankTextureBody;
private:
	std::string FrontTexturePath;
};