#include "invertedindex.h"

namespace fse {

bool InvertedIndex::is_word_exist(const std::string& word) const {
	return freq_dictionary_.find(word) != freq_dictionary_.end();
}

const WordInFiles& InvertedIndex::get_word_count(const std::string& word) const {
	return freq_dictionary_.at(word);
}

void InvertedIndex::update(const std::vector<std::string>& files_input) {
	syncclog() << "Start indexing files...\n";

	std::vector<InvertedIndexData> data;
	data.resize(files_input.size());

	for (auto i = 0; i < data.size();) {
		std::vector<std::thread> thrds{ std::thread::hardware_concurrency() };

		for (auto j = 0; j < thrds.size() && i < data.size(); ++j, ++i) {
			thrds[j] = std::thread(
				&InvertedIndex::index_file,
				this, std::cref(files_input[i]), i, std::ref(data[i])
			);
		}

		for (auto& thrd : thrds) {
			if (thrd.joinable()) {
				thrd.join();
			}
		}
	}

	freq_dictionary_ = std::accumulate(data.begin(), data.end(), InvertedIndexData{}, std::plus<InvertedIndexData>{});

	syncclog() << "End indexing files...\n";
}

void InvertedIndex::index_file(const std::string& content, size_t id, InvertedIndexData& data) {
	syncclog() << "Start indexing file with id = " << id << "\n";

	std::vector<std::string> words;
	TextParser::parse(content, words, max_file_words_count, max_word_size);

	std::for_each(words.begin(), words.end(), [&](auto& word) {
		data[word][id]++;
	});

	syncclog() << "End indexing file with id = " << id << "\n";
}

} // namespace fse