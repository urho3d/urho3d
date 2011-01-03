void initAudio()
{
    // Do a very basic test of scripting functionality by setting up sound & music in script
    
    // Lower mastervolumes slightly
    audio.setMasterGain(CHANNEL_MASTER, 0.75f);
    audio.setMasterGain(CHANNEL_MUSIC, 0.75f);

    // Play music only in singleplayer, otherwise there will be cacophony if testing on same machine
    if ((!isServer()) && (!isClient()))
    {
        Song@ song = cache.getResource("XM", "Music/NinjaGods.xm");
        song.play(0);
    }
}
