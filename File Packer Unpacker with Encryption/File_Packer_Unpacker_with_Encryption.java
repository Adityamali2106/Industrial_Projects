//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      File Packer Unpacker with Encryption
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Required packeages
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

import java.io.*;                   // For File Operations 
import java.util.*;                 // For regulaer operatons like scanner String etc

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Class Name      : Packer
//      Description     : This class packes all the .txt files into one file with its metadata and actual data 
//      Auther          : Aditya Vijay Mali
//      Date            : 16/09/2025
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Packer
{
    String Header = null;
    
    int iRet = 0;
    int i = 0, j = 0;
    
    byte Buffer[] = new byte[1024];
    byte bHeader[] = new byte[100];
    byte Key = 0x11;

    File packObj = null;

    FileOutputStream foobj = null;
    FileInputStream fiobj = null;

public 
    boolean FilePacker(String FolderName,String PackName,File fobj)
    {
        boolean bFlag = false;

        try
        {
            packObj = new File(PackName);

            packObj.createNewFile();

            foobj = new FileOutputStream(packObj);
            
            System.out.println("Folder is persent ");

            File fArr[] = fobj.listFiles();

            System.out.println("Number of Files in the folder are : "+fArr.length);

            for(i = 0; i < fArr.length;i++)
            {
                fiobj = new FileInputStream(fArr[i]);

                if(fArr[i].getName().endsWith(".txt") == true)
                {
                    // Header formation
                    Header = fArr[i].getName() + " " + fArr[i].length();

                    for(j = Header.length();j < 100;j++)
                    {
                        Header = Header + " ";
                    }

                    bHeader = Header.getBytes();

                    // Write header into pack file
                    foobj.write(bHeader,0,100);
                
                    // Read the data from input files from Marvellous folder 
                    while((iRet = fiobj.read(Buffer)) != -1)
                    {
                        //Encryption Logic
                        for (j = 0; j < iRet; j++)
                        {
                            Buffer[j] = (byte)(Buffer[j] ^ Key);
                        }

                        // Write the files data into pack file 
                        foobj.write(Buffer,0,iRet);
                    }
                }

                fiobj.close();
            }

            foobj.close();
            bFlag = true;
        }
        catch(Exception E)
        {
            System.out.println(E.getMessage());
        }
        
        return bFlag;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Class Name      : Unacker
//      Description     : This class Unpackes all the files which are packed into a pack filr  
//      Auther          : Aditya Vijay Mali
//      Date            : 16/09/2025
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Unpacker
{
    int FileSize = 0;
    int i = 0;
    int iRet = 0;

    String Header = null;
    String Tokens[] = null;
    
    File fobj = null;
    
    FileInputStream fiobj = null;
    FileOutputStream foobj = null;

    byte bHeader[] = new byte[100];
    byte Buffer[] = null;
    byte Key = 0x11;

public
    boolean File_Unpacker(String FileName, File fpackobj)
    {
        boolean bFlag = false;

        try
        {        
            fiobj = new FileInputStream(fpackobj);

            // Read the Header
            
            while ((iRet = fiobj.read(bHeader,0,100)) != -1)
            {
                Header = new String(bHeader);

                Header = Header.trim();

                Tokens = Header.split(" ");

                System.out.println("File Name : "+Tokens[0]);
                System.out.println("File Size : "+Tokens[1]);

                fobj = new File(Tokens[0]);
                
                fobj.createNewFile();

                foobj = new FileOutputStream(fobj);

                FileSize = Integer.parseInt(Tokens[1]);

                // Buffer for reading the data 
                Buffer = new byte[FileSize];

                // Read from Packed File 
                fiobj.read(Buffer,0,FileSize);

                // Decrypt the data
                for (i = 0; i < FileSize; i++) 
                {
                    Buffer[i] = (byte)(Buffer[i] ^ Key);
                }

                // Write into extracted File
                foobj.write(Buffer,0,FileSize); 
            }

            fiobj.close();
            foobj.close();
            bFlag = true;
        }
        catch(Exception E)
        {
            System.out.println(E.getMessage());
        }
        return bFlag;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//      Class Name      : File_Packer_Unpacker_with_Encryption
//      Description     : Entry Point class for the application all the user interaction are performed through this class 
//      Auther          : Aditya Vijay Mali
//      Date            : 16/09/2025
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

class File_Packer_Unpacker_with_Encryption
{
    public static void main(String A[]) throws Exception
    {
        boolean bRet = false;
        Scanner sobj = new Scanner(System.in);
        String Operation = null;
        String Packing = "Packing";
        String Unpacking = "Unpacking";

        System.out.println("Enter Operation to perform (Pack Folder in file or Unpack file): Packing or Unpacking");
        Operation = sobj.nextLine();

        if(Operation.equals(Packing))
        { 
            System.out.println("Enter the name of Folder :");
            String FolderName = sobj.nextLine();

            System.out.println("Enter the name of Packed File :");
            String PackName = sobj.nextLine();

            File fobj = new File(FolderName);

            if((fobj.exists()) && (fobj.isDirectory()))
            {
                Packer pobj = new Packer();

                bRet = pobj.FilePacker(FolderName,PackName,fobj);

                if (bRet) 
                {
                    System.err.println("File packing Successful");    
                }
                else
                {
                    System.out.println("File packing Unsuccessful");
                }
            }
            else
            {
                System.out.println("There is no such Folder ");
            }
        }
        else if (Operation.equals(Unpacking)) 
        {
            System.out.println("Enter the name of packing file : ");
            String FileName = sobj.nextLine();

            File fpackobj = new File(FileName);

            if (fpackobj.exists() == false) 
            {
                System.out.println("Error : There is no such packed file ");
                return;
            }
            else
            {
                Unpacker uobj = new Unpacker();

                bRet = uobj.File_Unpacker(FileName, fpackobj);

                if (bRet)
                {
                    System.out.println("Unpacking of "+FileName+" is Successful");    
                }
                else
                {
                    System.out.println("Unpacking of "+FileName+" is Unsuccessful");    
                }
            }    
        }
        else
        {
            System.out.println(Operation+" there is no such Operation");
        }

        sobj.close();
    }
}