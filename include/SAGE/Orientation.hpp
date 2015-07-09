// Orientation.hpp

#ifndef __SAGE_ORIENTATION_HPP__
#define __SAGE_ORIENTATION_HPP__

namespace SAGE
{
	enum class Orientation
	{
		None = 1 << 0,
		FlipHorizontal = 1 << 1,
		FlipVertical = 1 << 2,
		FlipBoth = (1 << 1) | (1 << 2)
	};

	inline Orientation operator|(Orientation p_EffectA, Orientation p_EffectB)
	{
		return static_cast<Orientation>(static_cast<int>(p_EffectA) | static_cast<int>(p_EffectB));
	}

	inline Orientation operator&(Orientation p_EffectA, Orientation p_EffectB)
	{
		return static_cast<Orientation>(static_cast<int>(p_EffectA)& static_cast<int>(p_EffectB));
	}
}

#endif
