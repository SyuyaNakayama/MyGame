#include "Color.h"

const float Color::MAX = 1.0f;

float Color::operator=(float val)
{
	val_ = val;
	if (val_ > Color::MAX) { val_ -= (int)val_; }
	if (val_ < 0.0f) { val_ += Color::MAX + (int)val_; }
	return val_;
}