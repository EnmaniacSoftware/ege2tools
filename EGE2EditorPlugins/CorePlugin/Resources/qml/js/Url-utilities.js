function extract_path_from_url(url) {
    var urlString = url.toString()

    var s
    if (urlString.startsWith("file:///")) {
        var k = urlString.charAt(9) === ':' ? 8 : 7
        s = urlString.substring(k)
    } else {
        s = urlString
    }

    console.debug("FROM CorePlugin")
    return s
}
