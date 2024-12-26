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
	std::string image_folder = std::string("images/" + folder_name);
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

void listen_on_port_8080() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        return;
    }

    // Set address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        return;
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        return;
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    // Accept an incoming connection
    while ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) >= 0) {
        std::cout << "Connection accepted." << std::endl;

        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello, World!";
        send(new_socket, response, strlen(response), 0);
		
        close(new_socket);
    }

    close(server_fd);
}

int main()
{
    srand(time(0));
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
				{ "random-sable", "sends a random sable picture, 50% chance to send faggot instead", bot.me.id},
    { "random-yote", "sends a random coyote picture, 50% chance to send faggot instead. WIP", bot.me.id},
    { "random-yeen", "sends a random hyena picture, 50% chance to send faggot instead. WIP", bot.me.id}
			};
			bot.global_bulk_command_create(commands);
		}

        bot.set_presence(dpp::presence(dpp::ps_online, dpp::at_game, "with queer animals!"));
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
  else if (event.command.get_command_name() == "random-yote") {
   dpp::embed wip_embed;
        
        wip_embed.set_title("Work in Progress")
                 .set_description("This command is still being developed. Please check back later.")
                 .set_color(dpp::colors::orange) // You can choose any color you prefer
                 .set_footer("Paskkal is a faggot!");

        event.reply(dpp::ir_dont_delete, wip_embed);
  }
  else if (event.command.get_command_name() == "random-yeen") {
   dpp::embed wip_embed;
        
        wip_embed.set_title("Work in Progress")
                 .set_description("This command is still being developed. Please check back later.")
                 .set_color(dpp::colors::orange) // You can choose any color you prefer
                 .set_footer("Pumpkin is a super faggot!");

        event.reply(dpp::ir_dont_delete, wip_embed);
  }
	});

	// Start the bot in a separate thread
    std::thread bot_thread([&bot]() {
        bot.start(dpp::st_wait);  // This will block the thread, but not the main thread
    });

    // Start the server to listen on port 8080 in the main thread
    listen_on_port_8080();

    // Join the bot thread (optional, but ensures the main thread waits for the bot to finish)
    bot_thread.join();

	return 0;
}
