#!/bin/bash
#pip - менеджер пакетов для Python
wget https://bootstrap.pypa.io/get-pip.py
python get-pip.py
#pyaudio
apt-get install portaudio19-dev
apt-get install python-dev
pip install pyaudio 
#распознавание речи
pip install --no-cache-dir speechrecognition
pip install monotonic
#google api client
pip install google-api-python-client
#folder
mkdir /var/iot/libs
cd /var/iot/libs
#gpio 
pip install pyA20
git clone https://github.com/duxingkei33/orangepi_PC_gpio_pyH3
cd orangepi_PC_gpio_pyH3
python setup.py install
#gpio pwm 
cd /var/iot/libs
git clone https://github.com/evergreen-it-dev/orangepwm.git
cd orangepwm
python init.py
#flac
apt-get install flac
#remove alsa errors
cd /var/iot/libs
git clone https://github.com/evergreen-it-dev/orangepi.git
python orangepi/alsa-config.py
#remove pulseaudio
apt-get remove pulseaudio
cd /usr/share/alsa/alsa.conf.d
rm 50-pulseaudio.conf
