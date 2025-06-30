local jsonParser = require("lualibs.json.json")

local resources = {
    fonts = require("resources.config.fonts"),
    images = require("resources.config.images"),
    messages = require("resources.config.messages"),
    sounds = require("resources.config.sounds"),
    musics = require("resources.config.musics"),
    animations = require("resources.config.animations"),
    texts = require("resources.config.texts"),
    svgs = require("resources.config.svgs"),
}

return jsonParser.stringify(resources, true)