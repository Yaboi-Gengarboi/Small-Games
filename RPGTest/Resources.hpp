// RPGTest
// Resources.hpp
// Created on 2022-10-14 by Justyn Durnford
// Last modified on 2022-11-28 by Justyn Durnford
// Header file for global resources.

#pragma once

#include "Namespace.hpp"

struct Resources
{
	Clock main_clock;
	Font consolas_font;
	Font pokemon_ds_font;
};

extern unique_ptr<Resources> resources;