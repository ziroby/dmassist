Jamis Buck's NPC Generator - Linux Build

You will need the qDecode 7.0.1 library installed at the same level as this directory,

In the qDecode-7.0.1 directory, do:

./configure
make

Come back to this directory and do:

make

npc.cgi should be in ../dnd/npc. Just link to the directory from your cgi-bin directory.

chmod 777 npc.cnt (counter file)

In your cgi-bin directory:

ln -s /path/dnd/npc npc

where path is the full path to npcgen.

Modify the templates in ../dnd/npc/tem to you liking.

Access the npc generator from http:/yourserverurl/cgi-bin/npc/npc.cgi and generate some npcs!

To build the console version, do:

make console

For help, type in:

./npc -h

in the ../dnd/npc directory

Enjoy!

Andargor
