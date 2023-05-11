#include "utils.hpp"

namespace my_utils
{
	std::unordered_map<std::string, std::vector<std::string>> read_from_file(std::string name_of_the_file)
	{
		fs::path current_dir = fs::current_path();
		fs::path parent_dir = current_dir.parent_path();
		fs::path filePath = parent_dir / "Textfiles";
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
			int i = 60;
			while (text_len - i > 65)
			{
				int space = text.find_last_of(' ', i);
				text.insert(space + 1, "\n");
				i += 60;
			}
		}
		return text;
	}
}