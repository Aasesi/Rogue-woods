#include "utils.hpp"

namespace my_utils
{
	std::unordered_map<std::string, std::vector<std::string>> read_from_file(std::string name_of_the_file)
	{
		fs::path current_dir = fs::current_path();
		fs::path parent_dir = current_dir.parent_path();
		fs::path filePath = parent_dir / "Assets";
		filePath /= name_of_the_file;
		if (!fs::exists(filePath))
		{
			std::cerr << "Error: file not found!" << std::endl;
		}

		std::unordered_map<std::string, std::vector<std::string>> data;

		std::ifstream file(filePath);
		if (!file.is_open())
		{
			std::cout << "Unable to open file: " << filePath << std::endl;
			return data;
		}

		std::regex keyword_regex("\\w+\\s*\\(");
		std::regex end_regex("\\)");

		std::string line;
		std::string keyword;
		while (getline(file, line))
		{
			std::smatch match;
			if (regex_search(line, match, keyword_regex))
			{
				// Extract the keyword from the matched string
				keyword = match[0].str();
				// Remove the "(" character from the end
				keyword.erase(keyword.length() - 1);
				// Remove any leading/trailing white space
				keyword = regex_replace(keyword, std::regex("\\s+$"), "");
				keyword = regex_replace(keyword, std::regex("^\\s+"), "");

				std::vector<std::string> lines;
				while (getline(file, line))
				{
					if (line.find(")") != std::string::npos)
					{
						break;
					}
					line = regex_replace(line, std::regex("^\\s+"), "");
					line = regex_replace(line, std::regex("\\s+$"), "");
					line += "\n";
					if (!line.empty())
					{
						lines.push_back(line);
					}
				}
				data[keyword] = lines;
			}
		}
		file.close();

		return data;
	}
	std::string format_text(std::string text)
	{
		int text_len = text.length();
		if (text_len > 70)
		{
			while (text_len > 70)
			{
				int space = text.find_last_of(' ', text_len - 60);
				text.insert(space + 1, "\n");
				text_len -= 60;
			}
		}
		text+="\n";
		return text;
	}
	std::queue<std::pair<std::string, std::string>> read_map(std::string name_of_the_file)
	{
		fs::path current_dir = fs::current_path();
		fs::path parent_dir = current_dir.parent_path();
		fs::path filePath = parent_dir / "Assets";
		filePath /= name_of_the_file;
		if (!fs::exists(filePath))
		{
			std::cerr << "Error: file not found!" << std::endl;
		}
		std::ifstream file(filePath);
		std::queue<std::pair<std::string, std::string>> lines;
		if (!file.is_open())
		{
			std::cout << "Unable to open file: " << filePath << std::endl;
			return lines;
		}
		std::string line;
		std::regex regex("(\\S+)\\s(\\S+)");
		while (getline(file, line))
		{
			std::smatch match;
			if (std::regex_match(line, match, regex))
			{
				lines.emplace(std::make_pair(match[1], match[2]));
			}
		}
		return lines;
	}
	std::string connect_strings_in_vector(std::vector<std::string> &vector_of_strings)
	{
		std::string connected_string;
		for (const std::string &str : vector_of_strings)
		{
			connected_string += str;
		}
		return connected_string;
	}
	std::vector<std::unique_ptr<Quest_option>> extract_text_for_quest(std::string name_of_the_file)
	{
		std::vector<std::unique_ptr<Quest_option>> quest_vec;
		fs::path current_dir = fs::current_path();
		fs::path parent_dir = current_dir.parent_path();
		fs::path filePath = parent_dir / "Assets";
		filePath /= name_of_the_file;
		if (!fs::exists(filePath))
		{
			std::cerr << "Error: file not found!" << std::endl;
		}
		std::ifstream file(filePath);
		std::queue<std::pair<std::string, std::string>> lines;
		if (!file.is_open())
		{
			std::cout << "Unable to open file: " << filePath << std::endl;
			return quest_vec;
		}
		std::string line;
		std::regex name_pattern("\"name\":\\s*\"([^\"]+)\"");
		std::regex text_pattern("\"text\": \"([^\"]+)\"");
		std::regex option_pattern("\"sub_options\": \\[");

		Quest_option *current_quest = nullptr;

		std::smatch match;

		while (getline(file, line))
		{
			if (line == "{")
			{
				if (current_quest != nullptr)
				{
					// zrob id dla quest_opption
					std::unique_ptr<Quest_option> new_quest = std::make_unique<Quest_option>("", "", "Option quest", current_quest, false);
					current_quest->add_sub_option(new_quest.get());
					current_quest = new_quest.get();
					quest_vec.push_back(std::move(new_quest));
				}
				else
				{
					std::unique_ptr<Quest_option> new_quest = std::make_unique<Quest_option>();
					current_quest = new_quest.get();
					quest_vec.push_back(std::move(new_quest));
					continue;
				}
			}
			else if (std::regex_search(line, match, name_pattern))
			{ 
				current_quest->assign_directi(match[1]);
			}
			else if (std::regex_search(line, match, text_pattern))
			{
				current_quest->assign_description(format_text(match[1]));
			}
			else if (std::regex_search(line, match, option_pattern))
			{
				continue;
			}
			else if (line == "}")
			{
				if (!current_quest->is_parent_null())
				{
					current_quest = current_quest->get_parent();
				}
			}
		}
		return quest_vec;
	}

}