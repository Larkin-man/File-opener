object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'FILE'
  ClientHeight = 290
  ClientWidth = 377
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -16
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 19
  object Out: TMemo
    Left = 140
    Top = 0
    Width = 237
    Height = 290
    Align = alRight
    Lines.Strings = (
      'Out')
    TabOrder = 0
  end
  object fopenBtn: TButton
    Left = 8
    Top = 40
    Width = 75
    Height = 25
    Caption = 'fopenBtn'
    TabOrder = 1
    OnClick = fopenBtnClick
  end
  object Edit1: TEdit
    Left = 89
    Top = 39
    Width = 38
    Height = 27
    TabOrder = 2
    Text = 'rb+'
  end
  object fileE: TEdit
    Left = 8
    Top = 8
    Width = 121
    Height = 27
    TabOrder = 3
    Text = 'in.txt'
  end
  object ReadBtn: TButton
    Left = 8
    Top = 72
    Width = 75
    Height = 25
    Caption = 'ReadBtn'
    TabOrder = 4
    OnClick = ReadBtnClick
  end
  object SizeBtn: TButton
    Left = 8
    Top = 103
    Width = 75
    Height = 25
    Caption = 'Size'
    TabOrder = 5
    OnClick = SizeBtnClick
  end
  object WriteBtn: TButton
    Left = 51
    Top = 201
    Width = 75
    Height = 25
    Caption = 'WriteBtn'
    TabOrder = 6
    OnClick = WriteBtnClick
  end
  object Edit2: TEdit
    Left = 8
    Top = 165
    Width = 41
    Height = 27
    NumbersOnly = True
    TabOrder = 7
    Text = '0'
  end
  object Pos: TUpDown
    Left = 49
    Top = 165
    Width = 18
    Height = 27
    Associate = Edit2
    Min = -999
    Max = 999
    TabOrder = 8
  end
  object fseekBtn: TButton
    Left = 69
    Top = 166
    Width = 48
    Height = 25
    Caption = 'fseek'
    TabOrder = 9
    OnClick = fseekBtnClick
  end
  object fcloseBtn: TButton
    Left = 8
    Top = 135
    Width = 75
    Height = 25
    Caption = 'fclose'
    TabOrder = 10
    OnClick = fcloseBtnClick
  end
  object WE: TEdit
    Left = 8
    Top = 200
    Width = 41
    Height = 27
    TabOrder = 11
    Text = 'WE'
  end
  object Button1: TButton
    Left = 8
    Top = 233
    Width = 75
    Height = 25
    Caption = 'Button1'
    TabOrder = 12
    OnClick = Button1Click
  end
  object ftellBTN: TButton
    Left = 89
    Top = 72
    Width = 45
    Height = 25
    Caption = 'ftell'
    TabOrder = 13
    OnClick = ftellBTNClick
  end
end
