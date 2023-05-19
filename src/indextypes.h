#pragma once

#include <string>
#include <map>
#include <functional>

namespace fse {

using WordInFiles		= std::map<size_t, size_t>;
using InvertedIndexData = std::map<std::string, WordInFiles>;

} // namespace fse

namespace std {

template<>
struct std::plus<fse::InvertedIndexData> {
	fse::InvertedIndexData operator()(
		const fse::InvertedIndexData& lhs,
		const fse::InvertedIndexData& rhs
	) const {
		fse::InvertedIndexData res = lhs;

		for (auto& w : rhs) {
			for (auto& wdoc : w.second) {
				res[w.first][wdoc.first] += wdoc.second;
			}
		}

		return res;
	}
};

} // namespace std