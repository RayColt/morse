<%@ page language="java" contentType="text/html; charset=ISO-8859-1"
    pageEncoding="ISO-8859-1"%>
    <%@ page import="morsepack.Morse"%>
 <%
	Morse morse = new Morse();
	String encode = request.getParameter("encode");
	String decode = request.getParameter("decode");
	String binary = request.getParameter("binary");
	if (!morse.isEmpty(encode)) {
		encode = morse.morse_encode(encode);
	} else {
		encode = "";
	}
	if (!morse.isEmpty(decode)) {
		decode = morse.morse_decode(decode);
	} else {
		decode = "";
	}
	if (!morse.isEmpty(binary)) {
		binary = morse.morse_binary(binary); 
	} else {
		binary = "";
	}
 %>
<!DOCTYPE html PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1">
<title>Morse Form</title>
</head>
<body>
<h1>Morse: 000 111 000 ... --- ...</h1>
<form action="?" method="post">
Encode Text to Morse:<br> <textarea name="encode" cols="50" rows="15"><% out.print(encode); %></textarea><br>
Encode Text to Binary Morse:<br> <textarea name="binary" cols="50" rows="15"><% out.print(binary); %></textarea><br>
Decode Morse or 000 111 000:<br> <textarea name="decode" cols="50" rows="20"><% out.print(decode); %></textarea>
<input type="submit">
</form>
</body>
</html>
