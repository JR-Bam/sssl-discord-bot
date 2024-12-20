#include <dpp/dpp.h>
#include <filesystem>
#include <vector>
#include <cstdlib>
#include <ctime>

#define _CRT_SECURE_NO_WARNINGS

/* Be sure to place your token in the line below.
 * Follow steps here to get a token:
 * https://dpp.dev/creating-a-bot-application.html
 * When you invite the bot, be sure to invite it with the 
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */


struct SelectedImage {
	int index;
	std::string FilePath;
};

SelectedImage randomImage(const std::string& folder_name) {
	std::string image_folder = std::string("./../images/" + folder_name);
	std::vector<std::string> image_files;

	for (const auto& entry : std::filesystem::directory_iterator(image_folder)) {
		if (entry.is_regular_file()) {
			std::string path = entry.path().string();
			image_files.push_back(path);
		}
	}

	if (!image_files.empty()) {
		int random_index = std::rand() % image_files.size();
		std::string random_image = image_files[random_index];
		return SelectedImage{ random_index, random_image };
	}
	else {
		return SelectedImage{ -1, "" };
	}
}

static dpp::message random_animal(const dpp::slashcommand_t& event, const std::string& animal) {
	srand(time(0));

	int win = std::rand() % 2;
	if (!win) {
		int faggot_chance = (std::rand() % 100 + 1);
		if (faggot_chance < 90)
			return dpp::message(event.command.channel_id, "faggot");
		else if (faggot_chance < 95)
			return dpp::message(event.command.channel_id, "### faggot. queer even.");
		else if (faggot_chance < 98) 
			return dpp::message(event.command.channel_id, "## I know what you are..");
		else 
			return dpp::message(event.command.channel_id, "# F A G G O T. Q U E E R!!!!!!!!");
	} 
	
	SelectedImage selectedImage = randomImage(animal);

	// If there are images, send a random one
	if (selectedImage.index != -1) {
		return dpp::message(event.command.channel_id, animal)
			.add_file(
				std::string(animal + ".png"),
				dpp::utility::read_file(selectedImage.FilePath)
			);
	}
	else {
		return dpp::message(event.command.channel_id, "No images found in the folder.");
	}
}

int main()
{
	/* Create bot cluster */
	dpp::cluster bot(std::getenv("BOT_TOKEN"));

	/* Output simple log messages to stdout */
	bot.on_log(dpp::utility::cout_logger());

	/* Register slash command here in on_ready */
	bot.on_ready([&bot](const dpp::ready_t& event) {
		/* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
		if (dpp::run_once<struct register_bot_commands>()) {
			std::vector<dpp::slashcommand> commands {
				{ "ping", "Pingpong!", bot.me.id },
				{ "random-samoyed", "sends a random samoyed picture, 50% chance to send faggot instead", bot.me.id},
				{ "random-snep", "sends a random snow leopard picture, 50% chance to send faggot instead", bot.me.id},
				{ "random-sable", "sends a random sable picture, 50% chance to send faggot instead", bot.me.id}
			};
			bot.global_bulk_command_create(commands);
		}
	});

	/* Handle slash command with the most recent addition to D++ features, coroutines! */
	bot.on_slashcommand([](const dpp::slashcommand_t& event) {
		if (event.command.get_command_name() == "ping") {
			event.reply("Pong!");
		}
		else if (event.command.get_command_name() == "random-snep") {
			event.reply(random_animal(event, "snowleopards"));
		}
		else if (event.command.get_command_name() == "random-samoyed") {
			event.reply(random_animal(event, "samoyeds"));
		}
		else if (event.command.get_command_name() == "random-sable") {
			event.reply(random_animal(event, "sables"));
		}
	});

	/* Start the bot */
	bot.start(dpp::st_wait);

	return 0;
}
