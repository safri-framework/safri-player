import QtQuick.Layouts 1.0
import QtQuick 2.2

Item {
    width: 300; height: 600

    ColumnLayout
    {
        width: parent.width
        height: parent.height

        TestDelegate
        {
            width: 30
            height: 30
            jsonContainer:"[\n    {\n        \"Album\": \"Redeemer of Souls (Deluxe)\",\n        \"AlbumArtist\": \"Judas Priest\",\n        \"Artist\": \"Judas Priest\",\n        \"Length\": 267,\n        \"MimeType\": \"spotify\",\n        \"Title\": \"Dragonaut\",\n        \"Track\": 1,\n        \"URL\": \"spotify:track:422SlzzovLoyhA5QAirMim\",\n        \"Year\": null\n    },\n    {\n        \"Album\": \"Redeemer of Souls (Deluxe)\",\n        \"AlbumArtist\": \"Judas Priest\",\n        \"Artist\": \"Judas Priest\",\n        \"Length\": 239,\n        \"MimeType\": \"spotify\",\n        \"Title\": \"Redeemer of Souls\",\n        \"Track\": 2,\n        \"URL\": \"spotify:track:19PjuOGInOfKNhU210HVNO\",\n        \"Year\": null\n    },\n    {\n        \"Album\": \"Redeemer of Souls (Deluxe)\",\n        \"AlbumArtist\": \"Judas Priest\",\n        \"Artist\": \"Judas Priest\",\n        \"Length\": 364,\n        \"MimeType\": \"spotify\",\n        \"Title\": \"Halls of Valhalla\",\n        \"Track\": 3,\n        \"URL\": \"spotify:track:4zX2bEgFHUIZV8rR3qsLor\",\n        \"Year\": null\n    }\n]"
        }

        TestDelegate
        {
            width: 30
            height: 30
            jsonContainer: "[\n    {\n        \"Album\": \"Redeemer of Souls (Deluxe)\",\n        \"AlbumArtist\": \"Judas Priest\",\n        \"Artist\": \"Judas Priest\",\n        \"Length\": 295,\n        \"MimeType\": \"spotify\",\n        \"Title\": \"Sword of Damocles\",\n        \"Track\": 4,\n        \"URL\": \"spotify:track:5i3HwQkEMoKiO1eBGCuUx1\",\n        \"Year\": null\n    },\n    {\n        \"Album\": \"Redeemer of Souls (Deluxe)\",\n        \"AlbumArtist\": \"Judas Priest\",\n        \"Artist\": \"Judas Priest\",\n        \"Length\": 236,\n        \"MimeType\": \"spotify\",\n        \"Title\": \"March of the Damned\",\n        \"Track\": 5,\n        \"URL\": \"spotify:track:1Sooku2g8u0vBZHIApKwL1\",\n        \"Year\": null\n    }\n]"
        }

        TestDelegate
        {
            width: 30
            height: 30
        }
    }
}
