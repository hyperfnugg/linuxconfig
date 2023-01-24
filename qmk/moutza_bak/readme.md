@Test
fun banan() {
(0..9).forEach {r ->
print("{")
(0..9).forEach {c ->
if(r < 5 && c < 5 || r  >= 5 && c >= 5)
print("k$r$c,")
else {
print("___,")
}
}
println("}, \\")
}
}