import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

public class ClientHttp {

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		//porta do request, geralmente a 80 é padrao
		final int portaRequest = 8082;
		//Vers�o do http ja com a escrita final do http
		final String vHttp = "HTTP/1.0\r\n";

		String host = "localhost";
		String url = "";
		String protocolHttp = "GET" + " " + url + vHttp;
		Socket socketConnect = null;
		BufferedReader in = null;
		PrintWriter out = null;

		try {
			//Verifica se existe conexao nessa porta e nesse host
			socketConnect = new Socket(host, portaRequest);
			out  = new PrintWriter(socketConnect.getOutputStream(), true);
			in  = new BufferedReader(new InputStreamReader(socketConnect.getInputStream()));

		}catch (java.io.IOException e) {
			System.out.println("A conexão não pode ser estabelecida");
			System.exit(1);
		}
		//Escreve o protocolo http no servidor
		out.println(protocolHttp);

		//Recebe do servidor a resposta e escreve na saida default do cliente
		try {
			String lineResponse = in.readLine();
			while(lineResponse != null) {
				System.out.println(lineResponse);
				lineResponse = in.readLine();
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

}
