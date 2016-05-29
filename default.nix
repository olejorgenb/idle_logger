{ stdenv, xorg }: 

stdenv.mkDerivation {
	name = "idle_logger";
	src = ./.;
	buildInputs = [ xorg.libX11 xorg.libXScrnSaver ];
}

