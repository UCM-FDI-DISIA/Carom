local animations = {
    {
        id = "normal_collide_animation",
        spriteSheetId = "normal_collide_VFX",
        scale = 0.5,
        cols = 8,
        rows = 1,
        animType = "KILLMYSELF",
        framelist = {
            { frame = 0, time = 3 },
            { frame = 1, time = 2 },
            { frame = 2, time = 3 },
            { frame = 3, time = 2 },
            { frame = 4, time = 1 },
            { frame = 5, time = 1 },
            { frame = 6, time = 1 }
        }
    },
    {
        id = "score_from_1_to_2",
        spriteSheetId = "roundScoreSprite",
        scale = 0.5,
        cols = 12,
        rows = 1,
        animType = "DISABLE",
        framelist = {
            { frame = 0, time = 3 },
            { frame = 1, time = 3 },
            { frame = 2, time = 3 },
            { frame = 3, time = 3 },
            { frame = 4, time = 3 },
            { frame = 5, time = 3 }
        }
    },
    {
        id = "score_from_2_to_3",
        spriteSheetId = "roundScoreSprite",
        scale = 0.5,
        cols = 12,
        rows = 1,
        animType = "DISABLE",
        framelist = {
            { frame = 6,  time = 3 },
            { frame = 7,  time = 3 },
            { frame = 8,  time = 3 },
            { frame = 9,  time = 3 },
            { frame = 10, time = 3 },
            { frame = 11, time = 3 }
        }
    },
}

return animations