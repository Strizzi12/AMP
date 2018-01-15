using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Security.Cryptography;
using System.Text;

namespace AMP {
	public class Controller {
		private bool WaitForTermination { get; set; }
		public bool PrintProcessTime { get; set; }
		private bool MoreInfo { get; set; }
		public string Infile { get; set; }

		private readonly PointCloud _pointCloud;

		public Controller() {
			_pointCloud = new PointCloud();
		}

		public void Terminate() {
			if (WaitForTermination) {
				Console.ReadLine();
			}
		}

		public void MyPrint(string input) {
			if (MoreInfo) {
				Console.WriteLine(input);
			}
		}

		public void ParseInputArguments(string[] args) {
			for (int i = 0; i < args.Length; i++) {
				switch (args[i]) {
					case "-w":
						WaitForTermination = true;
						continue;
					case "-p":
						PrintProcessTime = true;
						continue;
					case "-h":
						PrintHelp();
						continue;
					case "-v":
						MoreInfo = true;
						continue;
					case "-i":
						Infile = args[i];
						continue;
					case "-g":
						int anz = 0;
						float dx = 0.0f;
						float dy = 0.0f;
						float dz = 0.0f;
						try {
							//Split string at ,
							var input = args[i + 1].Split(',');
							if (input.Length == 4) {
								anz = Helper.TransformInput<int>(input[0]);
								dx = Helper.TransformInput<float>(input[1]);
								dy = Helper.TransformInput<float>(input[2]);
								dz = Helper.TransformInput<float>(input[3]);
							} else {
								Console.WriteLine("Error! Unknown argument detected.");
								break;
							}

						} catch (Exception e) {
							Console.WriteLine(e.Message);
							break;
						}
						_pointCloud.CreatePointCloud(anz, dx, dy, dz);
						i += 4; //Counter can be increased because the value of -g is already read.
						continue;
					default:
						Console.WriteLine("Error! Unknown argument detected.");
						PrintHelp();
						break;
				}
			}
		}



		private static void PrintHelp() {
			Console.WriteLine("Die Applikation kann wie folgt aufzurufen:");
			Console.WriteLine();
			Console.WriteLine("mmDistPt -i infile [-h] [-p] [-v] [-w] [-g n,dx,dy,dz]");
			Console.WriteLine();
			Console.WriteLine("-s startPath Gibt das Startverzeichnis an, ab dem die Dateien gelesen werden sollen;");
			Console.WriteLine("             die Option -s kann auch mehrfach angegeben werden, z.B. wenn zwei Partitionen durchsucht werden sollen");
			Console.WriteLine("-r [n]       Rekursives Lesen der Unterverzeichnisse; wenn n (bei n >= 1) angegeben, dann");
			Console.WriteLine("             bestimmt n die Tiefe der Rekursion; wird n nicht angegeben, dann werden");
			Console.WriteLine("             rekursiv alle unter dem Startverzeichnis stehenden Verzeichnisse und deren Dateien gelesen;");
			Console.WriteLine("-f           fileFilter fileFilter gibt an, welche Dateien gelesen werden sollen; z.B. *.iso oder bild*.jpg;");
			Console.WriteLine("             wird diese Option nicht angegeben, so werden alle Dateien gelesen;");
			Console.WriteLine("-t           maxThreads maximale Anzahl der Threads; wird diese Option nicht angegeben, dann wird die Anzahl der Threads automatisch optimiert.");
			Console.WriteLine("-h           Anzeige der Hilfe & Copyright Info; wird automatisch angezeigt, wenn beim Programmstart keinen Option angegeben wird.");
			Console.WriteLine("-p           Ausgabe der Prozesserungszeit auf stdout in Sekunden.Millisekunden");
			Console.WriteLine("-v           Erweiterte Ausgabe etwaiger Prozessierungsinformationen auf stdout");
			Console.WriteLine("-w           Warten auf eine Taste unmittelbar bevor die applikation terminiert.");
			Console.WriteLine();
			Console.WriteLine("Copyright© by Mike Thomas and Andreas Reschenhofer");
		}
	}
}