# -*- coding: utf-8 -*-

from xlrd import open_workbook
from string import *

def main():

    nameWorkBook=input("Type the name of the workbook without ext.\n")
    nameOutputFileTTCN3=input("Type the name of the output ttcn3 without ext:\n")

    ArrayData=getData(nameWorkBook)
    conversion2TTCN3(ArrayData,nameOutputFileTTCN3)

def getData(nFile):

    filename = nFile+".xls"
    book = open_workbook(filename)
    sheet_index = 1 #Se empieza desde la hoja ENTRADA Hasta la Hoja CONSOLIDADO
    total=[]

    ###constants definitions###
    zone0=0
    zone1=1
    ctrl0=0
    ctrl1=1
    dataBook=[]
    for sheet_index in range(1,4):
        sheet=book.sheet_by_index(sheet_index)
        row_index = 1
        value_Cars_WholeSheet = []
        value_Ctrl_WholeSheet = []
        value_Zone_WholeSheet = []
        for row_index in range(sheet.nrows):
            col_index=0
            for col_index in range(sheet.ncols):


                if (row_index>0):
                    if ( col_index==3 ):
                        value_Cars_WholeSheet.append(sheet.cell(row_index,col_index).value)
                        value_Ctrl_WholeSheet.append(ctrl0)
                        value_Zone_WholeSheet.append(zone0)
                        #valueWholeSheet.append(valueTuple)
                    elif ( col_index==4 ):
                        value_Cars_WholeSheet.append(sheet.cell(row_index,col_index).value)
                        value_Ctrl_WholeSheet.append(ctrl0)
                        value_Zone_WholeSheet.append(zone1)
                        #valueWholeSheet.append(valueTuple)
                    elif ( col_index==5 ):
                        value_Cars_WholeSheet.append(sheet.cell(row_index,col_index).value)
                        value_Ctrl_WholeSheet.append(ctrl1)
                        value_Zone_WholeSheet.append(zone0)
                        #valueWholeSheet.append(valueTuple)
                    elif ( col_index==6 ):
                        value_Cars_WholeSheet.append(sheet.cell(row_index,col_index).value)
                        value_Ctrl_WholeSheet.append(ctrl1)
                        value_Zone_WholeSheet.append(zone1)
                        #valueWholeSheet.append(valueTuple)
        dataBook.append(value_Cars_WholeSheet)
        dataBook.append(value_Ctrl_WholeSheet)
        dataBook.append(value_Zone_WholeSheet)
    return dataBook

def conversion2TTCN3(dataWorkBook,nameTTCN3):

    ###CONSTANTS###
    #nameArrays_TTCN3=['aEntryCars2Zone','aOutCars2Zone','aFreeSpotsExpecInZone']
    nameArrays_TTCN3=['aEntryCar','aCtrlEntryCar','aZoneEntryCar','aOutCar','aCtrlOutCar','aZoneOutCar',
                      'aExpectedSpots','aCtrlExpected','aZoneExpected']
    Length_Vec_Datas=len(dataWorkBook)
    Length_Rows_Vec=len(dataWorkBook[0])
    i=0

    #Creation of file *.ttcn3#
    nameFileTTCN3=nameTTCN3+".ttcn3"
    fileTTCN3=open(nameFileTTCN3,'w')

    #Creation of type array in TTCN-3#
    fileTTCN3.write("/*These are the definitions of the array*/\n")
    fileTTCN3.write("module "+nameTTCN3+" {\n")
    fileTTCN3.write("type integer generic_array_data["+str(Length_Rows_Vec)+
                    "];\n")
    fileTTCN3.write("const integer length_array_data:="+str(Length_Rows_Vec)+";\n")
    
    for i in range(len(dataWorkBook)):
        data=dataWorkBook[i]
        dataStr=str(data).replace("[","{")
        dataStr=dataStr.replace("]","}")
        dataStr=dataStr.replace(".0","")
        fileTTCN3.write("const generic_array_data "+nameArrays_TTCN3[i]+
                        ":="+dataStr+";\n")
    fileTTCN3.write("}")
    fileTTCN3.close()

#called to main function:
main()
