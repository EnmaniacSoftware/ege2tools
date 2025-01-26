// Checks if file name is valid.
// @param name File to verify.
// @return TRUE if file name is valid. Otherwise, FALSE.
function isValidFileName(name) {
    const regex = /^[a-zA-Z0-9._-]{1,255}$/
    return regex.test(name)
}
