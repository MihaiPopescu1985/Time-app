#pragma region Includes
#include <string>
#include <windows.h>
#include <comutil.h>
#pragma endregion

#pragma region Import the type libraries

#import "libid:2DF8D04C-5BFA-101B-BDE5-00AA0044DE52" \
    rename("RGB", "MSORGB") \
    rename("DocumentProperties", "MSODocumentProperties")
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\OFFICE12\\MSO.DLL" \
//    rename("RGB", "MSORGB") \
//    rename("DocumentProperties", "MSODocumentProperties")

using namespace Office;

#import "libid:0002E157-0000-0000-C000-000000000046"
// [-or-]
//#import "C:\\Program Files\\Common Files\\Microsoft Shared\\VBA\\VBA6\\VBE6EXT.OLB"

using namespace VBIDE;

#import "libid:00020813-0000-0000-C000-000000000046" \
    rename("DialogBox", "ExcelDialogBox") \
    rename("RGB", "ExcelRGB") \
    rename("CopyFile", "ExcelCopyFile") \
    rename("ReplaceText", "ExcelReplaceText") \
    no_auto_exclude
// [-or-]
//#import "C:\\Program Files\\Microsoft Office\\Office12\\EXCEL.EXE" \
//    rename("DialogBox", "ExcelDialogBox") \
//    rename("RGB", "ExcelRGB") \
//    rename("CopyFile", "ExcelCopyFile") \
//    rename("ReplaceText", "ExcelReplaceText") \
//    no_auto_exclude

#pragma endregion

class IOExcel
{
public:
	Excel::_ApplicationPtr XL;
	Excel::_WorksheetPtr pSheet;
	Excel::RangePtr pRange;

	std::string file_name;

	void Start_Excel();
	void Open_Workbook(std::string &s);
	void Save_Workbook();
	void Close_Workbook(){ XL->Quit(); return; };
	int Find_Project(std::string &s);
	void Write_Double(int row, int col, double val);
	void Write_String(int row, int col, std::string val);

	IOExcel(){ Start_Excel(); return; };
};

