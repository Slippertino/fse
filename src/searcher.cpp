#include "searcher.h"

namespace fse {

Searcher::Searcher(InvertedIndex& index) : index_(index)
{ }

QueryResult Searcher::search(const std::string& query) {
	syncclog() << "Start searching for query: \"" << query << "\"\n";

	QueryResult res;

	std::vector<std::string> words;
	TextParser::parse(query, words, max_query_words_count_);

	if (words.empty()) {
		log_finish_message(query, res.results.size());
		return res;
	}

	auto last = std::unique(words.begin(), words.end());
	words.erase(last, words.end());

	std::sort(words.begin(), words.end(), [&](const std::string& w1, const std::string& w2) {
		size_t w1_cnt{ 0 }, w2_cnt{ 0 };
		if (index_.is_word_exist(w1)) w1_cnt = index_.get_word_count(w1).size();
		if (index_.is_word_exist(w2)) w2_cnt = index_.get_word_count(w2).size();

		return w1_cnt < w2_cnt;
	});

	std::set<size_t> valid_files;
	get_included_files(words[0], valid_files);

	for (auto i = 1; i < words.size(); ++i) {
		std::set<size_t> cur;
		get_included_files(words[i], cur);

		if (cur.empty()) {
			continue;
		}

		std::set<size_t> temp;
		std::set_union(
			valid_files.begin(), valid_files.end(),
			cur.begin(), cur.end(),
			std::inserter(temp, temp.begin())
		);

		valid_files = std::move(temp);
	}

	if (valid_files.empty()) {
		log_finish_message(query, res.results.size());
		return res;
	}

	float max_rank = -1;
	for (auto& id : valid_files) {
		auto rank = calculate_file_rank(words, id);
		max_rank = std::max(rank, max_rank);
		res.results.push_back({ id, rank });
	}

	std::for_each(res.results.begin(), res.results.end(), [&](auto& val) {
		val.rank /= max_rank;
	});

	std::sort(res.results.begin(), res.results.end(), [](auto& v1, auto& v2) {
		return v1.rank > v2.rank;
	});

	log_finish_message(query, res.results.size());

	return res;
}

void Searcher::log_finish_message(const std::string& query, size_t count) {
	syncclog() << "Finish searching for query \"" << query << "\" with " << count << " files.\n";
}

float Searcher::calculate_file_rank(const std::vector<std::string>& words, size_t file_id) {
	float res = 0;

	for (auto& w : words) {
		if (!index_.is_word_exist(w)) {
			continue;
		}
		
		auto& wc = index_.get_word_count(w);

		if (wc.find(file_id) != wc.end()) {
			res += static_cast<float>(wc.at(file_id));
		}
	}

	return res;
}

void Searcher::get_included_files(const std::string& word, std::set<size_t>& files) {
	if (!index_.is_word_exist(word)) {
		return;
	}

	const auto& word_index = index_.get_word_count(word);

	std::transform(
		word_index.begin(),
		word_index.end(),
		std::inserter(files, files.begin()),
		[](auto& val) { return val.first; }
	);
}

} // namespace fse