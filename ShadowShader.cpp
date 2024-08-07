#include "ShadowShader.h"

void ShadowShader::CreateShader()
{
	if (sf::Shader::isAvailable())
		std::cout << "good Shader";
}
