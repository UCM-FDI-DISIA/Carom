package.path = package.path .. ";../../?.lua"

local jsonParser = require("external.lualibs.json.json")

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

local jsonString = jsonParser.stringify(resources, false)
print(jsonString)

return jsonString