#ifndef _SGK_GRAPHICS_TEXTURE_H_
#define _SGK_GRAPHICS_TEXTURE_H_

#include "SGK/Base/BasicDefinitions.h"

SGK_NAMESPACE_BEG

namespace Graphics {

	class Texture : public NonCopyable {
	public:
		Texture(const char* path);
		~Texture();

	private:
		class Impl;
		Impl* mImpl;
	};

}

SGK_NAMESPACE_END

#endif
