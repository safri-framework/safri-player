SAFRI_VERSION = 0.3.1

VERSTR = '\\"$${SAFRI_VERSION}\\"'
DEFINES += SAFRI_VERSION=\"$${VERSTR}\"

DEFINES += SELECTED_PLUGINS_FILE=\\\"selectedplugins.lst\\\"

android {

    DEFINES += ANDROID_LIB_PATH=\\\"/data/data/org.Safri/lib\\\"

}
