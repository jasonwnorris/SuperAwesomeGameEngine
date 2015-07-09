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

	inline Orientation operator|(Orientation pEffectA, Orientation pEffectB)
	{
		return static_cast<Orientation>(static_cast<int>(pEffectA) | static_cast<int>(pEffectB));
	}

	inline Orientation operator&(Orientation pEffectA, Orientation pEffectB)
	{
		return static_cast<Orientation>(static_cast<int>(pEffectA)& static_cast<int>(pEffectB));
	}
}

#endif
