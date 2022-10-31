// TicTacToe
// SFMLFunctions.cpp
// Created on 2022-03-10 by Justyn Durnford
// Last modified on 2022-03-10 by Justyn Durnford
// Implementation file for SFMLFunctions.hpp.

#include "SFMLFunctions.hpp"

void load_texture(Texture& texture, const string& filedir)
{
	if (!texture.loadFromFile(filedir))
	{
		// Try again.
		if (!texture.loadFromFile(filedir))
		{
			cout << "ERROR: Could not load texture file " << filedir << "\n";
			cout << "Check to make sure the file is located in the\n";
			cout << "\"resources\" folder." << endl;

			exit(EXIT_FAILURE);
		}
	}
}