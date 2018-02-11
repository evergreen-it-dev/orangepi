import os, re

filo = "/usr/share/alsa/alsa.conf"
replace = [
    ["pcm.front cards.pcm.front", "#pcm.front cards.pcm.front"],
    ["pcm.rear cards.pcm.rear","#pcm.rear cards.pcm.rear"],
    ["pcm.center_lfe cards.pcm.center_lfe","#pcm.center_lfe cards.pcm.center_lfe"],
    ["pcm.side cards.pcm.side","#pcm.side cards.pcm.side"],
    ["pcm.surround21 cards.pcm.surround21","#pcm.surround21 cards.pcm.surround21"],
    ["pcm.surround40 cards.pcm.surround40","#pcm.surround40 cards.pcm.surround40"],
    ["pcm.surround41 cards.pcm.surround41","#pcm.surround41 cards.pcm.surround41"],
    ["pcm.surround50 cards.pcm.surround50","#pcm.surround50 cards.pcm.surround50"],
    ["pcm.surround51 cards.pcm.surround51","#pcm.surround51 cards.pcm.surround51"],
    ["pcm.surround71 cards.pcm.surround71","#pcm.surround71 cards.pcm.surround71"],
    ["pcm.iec958 cards.pcm.iec958","#pcm.iec958 cards.pcm.iec958"],
    ["pcm.spdif iec958","#pcm.spdif iec958"],
    ["pcm.hdmi cards.pcm.hdmi","#pcm.hdmi cards.pcm.hdmi"],
    ["pcm.dmix cards.pcm.dmix","#pcm.dmix cards.pcm.dmix"],
    ["pcm.dsnoop cards.pcm.dsnoop","#pcm.dsnoop cards.pcm.dsnoop"],
    ["pcm.modem cards.pcm.modem","#pcm.modem cards.pcm.modem"],
    ["pcm.phoneline cards.pcm.phoneline","#pcm.phoneline cards.pcm.phoneline"]
]
input_file = open(filo).read()
output_file = open(filo,"w")

for string in replace:
    input_file = re.sub(str(string[0]),str(string[1]),input_file)

output_file.write(input_file)
output_file.close()
