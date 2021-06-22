#ifndef Static_FormatResult_h_INCLUDED
#define Static_FormatResult_h_INCLUDED

#include <string_view>

namespace Static {

struct FormatResult
{
	bool isTruncated;
	std::string_view str;
};

} // namespace Static

#endif // Static_FormatResult_h_INCLUDED
