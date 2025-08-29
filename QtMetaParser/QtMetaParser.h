#pragma once
#include <pro.h>
#include <vector>
#include <bytes.hpp>
#include <kernwin.hpp>
#include <search.hpp>
#include <map>
#include <algorithm>
#include "QtMetaParser.h"
#include "./Public/IDAWrapper.h"
#include "Common.h"

std::map<unsigned int, std::string> gMapQMetaType;

template<typename T>
struct QMetaObject_d
{
	T superdata;
	T stringdata;
	T data;
	T static_metacall;
	T relatedMetaObjects;
	//reserved for future use
	T extradata;
};

struct QMethodData_4
{
	//����ǩ��
	std::string methodSignature;
	//��������
	std::string paramName;
	//����ֵ����
	std::string retType;
	//������Դ��
	std::string functionSrc;
};

struct QMethodData
{
	//��������
	std::string methodName;
	//����ֵ����
	std::string retType;
	//��������
	unsigned int argCount;
	//��������ƫ��
	std::uint32_t paramOffset;
	//��������
	std::vector<std::string> paramsType;
	//������
	std::vector<std::string> paramsName;
};

void InitQMetaTypeMap()
{
	gMapQMetaType[0] = "UnknownType";
	gMapQMetaType[1] = "Bool";
	gMapQMetaType[2] = "Int";
	gMapQMetaType[3] = "UInt";
	gMapQMetaType[4] = "LongLong";
	gMapQMetaType[5] = "ULongLong";
	gMapQMetaType[6] = "Double";
	gMapQMetaType[7] = "QChar";
	gMapQMetaType[8] = "QVariantMap";
	gMapQMetaType[9] = "QVariantList";
	gMapQMetaType[10] = "QString";
	gMapQMetaType[11] = "QStringList";
	gMapQMetaType[12] = "QByteArray";
	gMapQMetaType[13] = "QBitArray";
	gMapQMetaType[14] = "QDate";
	gMapQMetaType[15] = "QTime";
	gMapQMetaType[16] = "QDateTime";
	gMapQMetaType[17] = "QUrl";
	gMapQMetaType[18] = "QLocale";
	gMapQMetaType[19] = "QRect";
	gMapQMetaType[20] = "QRectF";
	gMapQMetaType[21] = "QSize";
	gMapQMetaType[22] = "QSizeF";
	gMapQMetaType[23] = "QLine";
	gMapQMetaType[24] = "QLineF";
	gMapQMetaType[25] = "QPoint";
	gMapQMetaType[26] = "QPointF";
	gMapQMetaType[27] = "QRegExp";
	gMapQMetaType[28] = "QVariantHash";
	gMapQMetaType[29] = "QEasingCurve";
	gMapQMetaType[30] = "QUuid";
	gMapQMetaType[31] = "VoidStar";
	gMapQMetaType[32] = "Long";
	gMapQMetaType[33] = "Short";
	gMapQMetaType[34] = "Char";
	gMapQMetaType[35] = "ULong";
	gMapQMetaType[36] = "UShort";
	gMapQMetaType[37] = "UChar";
	gMapQMetaType[38] = "Float";
	gMapQMetaType[39] = "QObjectStar";
	gMapQMetaType[40] = "SChar";
	gMapQMetaType[41] = "QVariant";
	gMapQMetaType[42] = "QModelIndex";
	gMapQMetaType[43] = "Void";
	gMapQMetaType[44] = "QRegularExpression";
	gMapQMetaType[45] = "QJsonValue";
	gMapQMetaType[46] = "QJsonObject";
	gMapQMetaType[47] = "QJsonArray";
	gMapQMetaType[48] = "QJsonDocument";
	gMapQMetaType[49] = "QByteArrayList";
	gMapQMetaType[50] = "QPersistentModelIndex";
	gMapQMetaType[51] = "Nullptr";
	gMapQMetaType[52] = "QCborSimpleType";
	gMapQMetaType[53] = "QCborValue";
	gMapQMetaType[54] = "QCborArray";
	gMapQMetaType[55] = "QCborMap";

	gMapQMetaType[64] = "QFont";
	gMapQMetaType[65] = "QPixmap";
	gMapQMetaType[66] = "QBrush";
	gMapQMetaType[67] = "QColor";
	gMapQMetaType[68] = "QPalette";
	gMapQMetaType[69] = "QIcon";
	gMapQMetaType[70] = "QImage";
	gMapQMetaType[71] = "QPolygon";
	gMapQMetaType[72] = "QRegion";
	gMapQMetaType[73] = "QBitmap";
	gMapQMetaType[74] = "QCursor";
	gMapQMetaType[75] = "QKeySequence";
	gMapQMetaType[76] = "QPen";
	gMapQMetaType[77] = "QTextLength";
	gMapQMetaType[78] = "QTextFormat";
	gMapQMetaType[79] = "QMatrix";
	gMapQMetaType[80] = "QTransform";
	gMapQMetaType[81] = "QMatrix4x4";
	gMapQMetaType[82] = "QVector2D";
	gMapQMetaType[83] = "QVector3D";
	gMapQMetaType[84] = "QVector4D";
	gMapQMetaType[85] = "QQuaternion";
	gMapQMetaType[86] = "QPolygonF";
	gMapQMetaType[87] = "QColorSpace";

	gMapQMetaType[121] = "QSizePolicy";
	gMapQMetaType[1024] = "User";
}


template<typename T>
class QtMetaParser
{
public:
	QtMetaParser();
	void StartParse();
private:
	bool parseMetaData_4(T addr);
	bool parseStringData(T addr);
	bool parseMetaData(T addr);
	std::string getParamType(std::uint32_t paramIndex);
private:
	std::vector<std::string> stringDataList;
	QMetaObject_d<T> metaObject;
};


template<typename T>
QtMetaParser<T>::QtMetaParser()
{
	InitQMetaTypeMap();
}

template<typename T>
std::string QtMetaParser<T>::getParamType(std::uint32_t paramIndex)
{
	if (paramIndex & 0x80000000) {
		return this->stringDataList[paramIndex & 0xFFFFFFF];
	}
	std::map<unsigned int, std::string>::iterator it = gMapQMetaType.find(paramIndex);
	if (it != gMapQMetaType.end()) {
		return it->second;
	}
	return "Unknown";
}

//����,�û�ʶ����������б�
std::vector<std::string> recognizeFunctionParamsNameList(std::string paramNameSignature)
{
	std::vector<std::string> retList;
	size_t paramStart = paramNameSignature.find(',');
	while (paramStart != -1) {
		std::string tmpParamName = paramNameSignature.substr(0, paramStart);
		retList.push_back(tmpParamName);
		paramNameSignature = paramNameSignature.substr(paramStart + 1);
		paramStart = paramNameSignature.find(',');
	}
	retList.push_back(paramNameSignature);
	return retList;
}

//����,����ʶ����ǩ��,���ز�������
std::vector<std::string> recognizeFunctionParamsTypeList(std::string& functionSignature)
{
	std::vector<std::string> retList;

	size_t paramStart = functionSignature.find('(');
	size_t paramEnd = functionSignature.rfind(')');
	if (paramStart == -1 || paramEnd == -1) {
		return retList;
	}
	std::string paramListString = functionSignature.substr(paramStart + 1, paramEnd - paramStart - 1);
	std::string currentParam;
	size_t openBrackets = 0;
	for (char c : paramListString) {
		if (c == '<') {
			++openBrackets;
			currentParam += c;
		}
		else if (c == '>') {
			--openBrackets;
			currentParam += c;
		}
		else if (c == ',' && openBrackets == 0) {
			retList.push_back(currentParam);
			currentParam.clear();
		}
		else {
			currentParam += c;
		}
	}
	retList.push_back(currentParam);
	return retList;
}

template<typename T>
bool QtMetaParser<T>::parseStringData(T addr)
{
	T startAddr = addr;
	struct stringElement
	{
		std::uint32_t startFlag;
		std::uint32_t len;
		T unknown;
		T offset;
	};
	while (true) {
		stringElement tmpElement = { 0 };
		if (get_bytes(&tmpElement, sizeof(stringElement), startAddr) == -1) {
			return false;
		}
		if (tmpElement.startFlag != -1 || tmpElement.unknown) {
			break;
		}
		std::string tmpStr;
		if (tmpElement.len) {
			tmpStr = IDAWrapper::get_shortstring(startAddr + tmpElement.offset);
		}
		stringDataList.push_back(tmpStr);
		startAddr = startAddr + sizeof(stringElement);
	};
	return true;
}

template<typename T>
bool QtMetaParser<T>::parseMetaData(T addr)
{
	struct QtMetaDataHeader
	{
		std::uint32_t revision;
		std::uint32_t classname;
		std::uint32_t classinfoCount, classinfoData;
		std::uint32_t methodCount, methodData;
		std::uint32_t propertyCount, propertyData;
		std::uint32_t enumeratorCount, enumeratorData;
		std::uint32_t constructorCount, constructorData;
		std::uint32_t flags;
		std::uint32_t signalCount;
	};

	T startAddr = addr;
	QtMetaDataHeader header;
	get_bytes(&header, sizeof(QtMetaDataHeader), startAddr);
	startAddr = startAddr + sizeof(QtMetaDataHeader);


	std::vector<QMethodData> signalMethodList;
	std::vector<QMethodData> slotMethodList;

	for (unsigned int n = 0; n < header.signalCount; ++n) {
		QMethodData tmpMethod;
		unsigned int signalIdx = get_dword(startAddr);
		tmpMethod.methodName = this->stringDataList[signalIdx];
		tmpMethod.argCount = get_dword(startAddr + 0x4);
		tmpMethod.paramOffset = get_dword(startAddr + 0x8);
		unsigned int tag = get_dword(startAddr + 0xC);
		unsigned int flags = get_dword(startAddr + 0x10);
		signalMethodList.push_back(tmpMethod);
		startAddr = startAddr + 0x14;
	}

	for (unsigned int n = 0; n < header.methodCount - header.signalCount; ++n) {
		QMethodData tmpMethod;
		unsigned int slotIdx = get_dword(startAddr);
		tmpMethod.methodName = this->stringDataList[slotIdx];
		tmpMethod.argCount = get_dword(startAddr + 0x4);
		tmpMethod.paramOffset = get_dword(startAddr + 0x8);
		unsigned int tag = get_dword(startAddr + 0xC);
		unsigned int flags = get_dword(startAddr + 0x10);
		slotMethodList.push_back(tmpMethod);
		startAddr = startAddr + 0x14;
	}

	for (unsigned int n = 0; n < signalMethodList.size(); ++n) {
		ea_t paramAddr = addr + (signalMethodList[n].paramOffset * 4);
		//��һ��һ���Ƿ���ֵ
		signalMethodList[n].retType = getParamType(get_dword(paramAddr));
		paramAddr = paramAddr + 4;
		//������������
		for (unsigned int m = 0; m < signalMethodList[n].argCount; ++m) {
			signalMethodList[n].paramsType.push_back(getParamType(get_dword(paramAddr)));
			paramAddr = paramAddr + 4;
		}
		//����������
		for (unsigned int m = 0; m < signalMethodList[n].argCount; ++m) {
			signalMethodList[n].paramsName.push_back(stringDataList[get_dword(paramAddr)]);
			paramAddr = paramAddr + 4;
		}
	}

	for (unsigned int n = 0; n < slotMethodList.size(); ++n) {
		ea_t paramAddr = addr + (slotMethodList[n].paramOffset * 4);
		//��һ��һ���Ƿ���ֵ
		slotMethodList[n].retType = getParamType(get_dword(paramAddr));
		paramAddr = paramAddr + 4;
		//������������
		for (unsigned int m = 0; m < slotMethodList[n].argCount; ++m) {
			slotMethodList[n].paramsType.push_back(getParamType(get_dword(paramAddr)));
			paramAddr = paramAddr + 4;
		}
		//����������
		for (unsigned int m = 0; m < slotMethodList[n].argCount; ++m) {
			slotMethodList[n].paramsName.push_back(stringDataList[get_dword(paramAddr)]);
			paramAddr = paramAddr + 4;
		}
	}

	//��ʼ������
	int index = 0;
	msg("signal count(%d):\n", signalMethodList.size());
	for (unsigned int n = 0; n < signalMethodList.size(); ++n) {
		std::string methodMsg = signalMethodList[n].retType + " " + signalMethodList[n].methodName + "(";
		for (unsigned int m = 0; m < signalMethodList[n].argCount; ++m) {
			methodMsg = methodMsg + signalMethodList[n].paramsType[m] + " " + signalMethodList[n].paramsName[m] + ",";
		}
		if (signalMethodList[n].argCount) {
			methodMsg.pop_back();
		}
		methodMsg = methodMsg + ")";
		msg("%d %s\n", index++, methodMsg.c_str());
	}

	msg("slot count(%d):\n", slotMethodList.size());
	for (unsigned int n = 0; n < slotMethodList.size(); ++n) {
		std::string methodMsg = slotMethodList[n].retType + " " + slotMethodList[n].methodName + "(";
		for (unsigned int m = 0; m < slotMethodList[n].argCount; ++m) {
			methodMsg = methodMsg + slotMethodList[n].paramsType[m] + " " + slotMethodList[n].paramsName[m] + ",";
		}
		if (slotMethodList[n].argCount) {
			methodMsg.pop_back();
		}
		methodMsg = methodMsg + ")";
		msg("%d %s\n", index++, methodMsg.c_str());
	}
	return true;
}

template<typename T>
bool QtMetaParser<T>::parseMetaData_4(T addr)
{
	struct QtMetaDataHeader
	{
		std::uint32_t revision;
		std::uint32_t classname;
		std::uint32_t classinfoCount, classinfoData;
		std::uint32_t methodCount, methodData;
		std::uint32_t propertyCount, propertyData;
		std::uint32_t enumeratorCount, enumeratorData;
		std::uint32_t constructorCount, constructorData;
		std::uint32_t flags;
		std::uint32_t signalCount;
	};
	T startAddr = addr;
	QtMetaDataHeader header;
	get_bytes(&header, sizeof(QtMetaDataHeader), startAddr);
	startAddr = startAddr + sizeof(QtMetaDataHeader);

	std::vector<QMethodData_4> signalMethodList;
	std::vector<QMethodData_4> slotMethodList;

	for (unsigned int n = 0; n < header.signalCount; ++n) {

		QMethodData_4 tmpMethod;
		unsigned int signalOffset = get_dword(startAddr);
		//����ǩ��,�����������ƺͺ�������
		tmpMethod.methodSignature = IDAWrapper::get_shortstring(metaObject.stringdata + signalOffset);
		//ֻ�в���������
		tmpMethod.paramName = IDAWrapper::get_shortstring(metaObject.stringdata + get_dword(startAddr + 0x4));
		tmpMethod.retType = IDAWrapper::get_shortstring(metaObject.stringdata + get_dword(startAddr + 0x8));
		unsigned int tag = get_dword(startAddr + 0xC);
		unsigned int flags = get_dword(startAddr + 0x10);
		signalMethodList.push_back(tmpMethod);
		startAddr = startAddr + 0x14;
	}

	for (unsigned int n = 0; n < header.methodCount - header.signalCount; ++n) {
		QMethodData_4 tmpMethod;
		unsigned int slotOffset = get_dword(startAddr);
		//����ǩ��,�����������ƺͺ�������
		tmpMethod.methodSignature = IDAWrapper::get_shortstring(metaObject.stringdata + slotOffset);
		//ֻ�в���������
		tmpMethod.paramName = IDAWrapper::get_shortstring(metaObject.stringdata + get_dword(startAddr + 0x4));
		tmpMethod.retType = IDAWrapper::get_shortstring(metaObject.stringdata + get_dword(startAddr + 0x8));
		unsigned int tag = get_dword(startAddr + 0xC);
		unsigned int flags = get_dword(startAddr + 0x10);
		slotMethodList.push_back(tmpMethod);
		startAddr = startAddr + 0x14;
	}

	//��ʼ���������ĺ���ǩ��
	std::string className = IDAWrapper::get_shortstring(metaObject.stringdata);
	for (unsigned int n = 0; n < signalMethodList.size(); ++n) {
		if (signalMethodList[n].retType == "") {
			signalMethodList[n].retType = "void";
		}
		std::string funcSrc = signalMethodList[n].retType + " ";
		size_t start = signalMethodList[n].methodSignature.find('(');
		size_t end = signalMethodList[n].methodSignature.find(')');
		if (start == -1 || end == -1) {
			return false;
		}
		std::string functionName = className + "::" + signalMethodList[n].methodSignature.substr(0, start);
		funcSrc = funcSrc + functionName + "(";
		//����������Ϊ0
		if (end != start + 1) {
			//��������Ϊ1
			if (!std::count(signalMethodList[n].methodSignature.begin(), signalMethodList[n].methodSignature.end(), ',')) {
				funcSrc = funcSrc + signalMethodList[n].methodSignature.substr(start + 1, end - start - 1) + " " + signalMethodList[n].paramName;
			}
			else {
				std::vector<std::string> pararmNameList = recognizeFunctionParamsNameList(signalMethodList[n].paramName);
				std::vector<std::string> paramTypeList = recognizeFunctionParamsTypeList(signalMethodList[n].methodSignature);
				if (paramTypeList.size() != pararmNameList.size()) {
					//�����Ǹ�д�Ĵ����������
					return false;
				}
				for (unsigned int k = 0; k < paramTypeList.size(); ++k) {
					funcSrc = funcSrc + paramTypeList[k] + " " + pararmNameList[k] + ",";
				}
				funcSrc.pop_back();
			}
		}
		funcSrc = funcSrc + ")";
		signalMethodList[n].functionSrc = funcSrc;
	}

	for (unsigned int n = 0; n < slotMethodList.size(); ++n) {
		if (slotMethodList[n].retType == "") {
			slotMethodList[n].retType = "void";
		}
		std::string funcSrc = slotMethodList[n].retType + " ";
		size_t start = slotMethodList[n].methodSignature.find('(');
		size_t end = slotMethodList[n].methodSignature.find(')');
		if (start == -1 || end == -1) {
			return false;
		}
		std::string functionName = className + "::" + slotMethodList[n].methodSignature.substr(0, start);
		funcSrc = funcSrc + functionName + "(";
		//����������Ϊ0
		if (end != start + 1) {
			//��������Ϊ1
			if (!std::count(slotMethodList[n].methodSignature.begin(), slotMethodList[n].methodSignature.end(), ',')) {
				funcSrc = funcSrc + slotMethodList[n].methodSignature.substr(start + 1, end - start - 1) + " " + slotMethodList[n].paramName;
			}
			else {
				std::vector<std::string> pararmNameList = recognizeFunctionParamsNameList(slotMethodList[n].paramName);
				std::vector<std::string> paramTypeList = recognizeFunctionParamsTypeList(slotMethodList[n].methodSignature);
				if (paramTypeList.size() != pararmNameList.size()) {
					//�����Ǹ�д�Ĵ����������
					return false;
				}
				for (unsigned int k = 0; k < paramTypeList.size(); ++k) {
					funcSrc = funcSrc + paramTypeList[k] + " " + pararmNameList[k] + ",";
				}
				funcSrc.pop_back();
			}
		}
		funcSrc = funcSrc + ")";
		slotMethodList[n].functionSrc = funcSrc;
	}

	//����������ʼ������������������
	int index = 0;
	msg("signal count(%d):\n", signalMethodList.size());
	for (unsigned int n = 0; n < signalMethodList.size(); ++n) {
		msg("%d %s\n", index++, signalMethodList[n].functionSrc.c_str());
	}
	msg("slot count(%d):\n", slotMethodList.size());
	for (unsigned int n = 0; n < slotMethodList.size(); ++n) {
		msg("%d %s\n", index++, slotMethodList[n].functionSrc.c_str());
	}
	return true;
}

/**
 * @brief ��ָ�������ж���������һ���ַ�����
 *
 * @param segment_name Ҫ�����Ľ������� (e.g., ".rdata", ".data")��
 * @param search_text Ҫ�������ı���
 * @return bool ����ҵ��򷵻� true��
 */
bool search_string_in_segment(const char* segment_name, const char* search_text)
{
	segment_t* seg = get_segm_by_name(segment_name);
	if (seg == nullptr)
	{
		// ��Ĭʧ�ܣ���ΪĳЩ�������ܲ����� (e.g., .rdata vs .rodata)
		// msg("[-] Segment '%s' not found, skipping.\n", segment_name);
		return false;
	}

	ea_t start_ea = seg->start_ea;
	ea_t end_ea = seg->end_ea;
	const size_t text_len = strlen(search_text);

	if (text_len == 0)
	{
		return false; // ���������ַ���
	}

	//msg("[*] Binary searching for '%s' in segment %s (0x%a to 0x%a)\n", search_text, segment_name, start_ea, end_ea);

	ea_t found_ea = bin_search(
		start_ea,
		end_ea,
		(const uchar*)search_text,  // image: Ҫ�������ֽ�
		nullptr,                    // mask:  �����룬��ȷ����
		text_len,                   // len:   �ֽڳ���
		SEARCH_DOWN | SEARCH_CASE   // flags: ������������Сд����
	);

	if (found_ea != BADADDR)
	{
		//msg("  [+] Found a match at address 0x%a\n", found_ea);
		return true;
	}

	return false;
}

template<typename T>
void QtMetaParser<T>::StartParse()
{
	const char* segment_name = ".data";
	// 1. �������Ʋ��ҽ���
	segment_t* data_seg = get_segm_by_name(segment_name);

	if (data_seg == nullptr)
	{
		msg("[-] Segment '%s' not found.\n", segment_name);
		return;
	}

	ea_t seg_start = data_seg->start_ea;
	ea_t seg_end = data_seg->end_ea;

	size_t find_count = 0;

	msg("[*] Start searching for QT metadata entries in %s (from 0x%a to 0x%a)\n",
		segment_name, seg_start, seg_end);

	// 2. ���������ڵ�ÿһ���Ѷ���ġ�ͷ����head��
	// a ��head�� is the starting address of an instruction or data item.
	for (ea_t head = seg_start; head < seg_end; head = next_head(head, seg_end))
	{
		// 3. ��ȡ��ַ�ı�־λ (flags)
		flags64_t flags = get_flags(head);

		// 4. �ж������ͷ���Ƿ񱻶���Ϊ����
		if (is_data(flags))
		{
			// 5. ��������ݣ���ȡ����ӡ�����Ϣ
			qstring item_name;
			get_visible_name(&item_name, head); // ��ȡ����

			asize_t item_size = get_item_size(head); // ��ȡ��С
			if (item_size > 0x40)
			{
				// Ŀǰ����QT6 64λ�汾��QMetaObjectҲ��0x40���ֽڴ�С
				continue;
			}

			//msg("  - Address: 0x%a | Name: %s | Size: %u bytes\n", head, item_name.c_str(), (unsigned int)item_size);

			// ������һ�ε��ַ�����
			this->stringDataList.clear();

			// ��ȡ metaObject �ṹ�����Խ���
			metaObject = { 0 };
			if (get_bytes(&metaObject, sizeof(metaObject), head) != sizeof(metaObject)) {
				// ��ȡʧ�ܣ�����
				// ��̬����δ�Ż��汾��QTʱ�����������������ʱ�����ͨ����Ŀ������������������(������ЩstaticMetaObject�����ʼ����ɺ�)���Լ��ɽ��
				continue;
			}

			int revision = get_dword(metaObject.data);
			if (revision > 0)
			{
				if (revision == 5 || revision == 6) {
					// Qt4.x ���Ԫ����
					if (parseMetaData_4(metaObject.data))
					{
						find_count++;
					}
				}
				else if (revision == 7) {
					// Qt5 ����Ƚ��� stringdata �ٽ��� data
					if (!parseStringData(metaObject.stringdata)) {
						msg("parseStringData failed for %s @ %08X\n", item_name, head);
						continue;
					}
					if (parseMetaData(metaObject.data))
					{
						find_count++;
					}
				}
				else if (revision > 7 && revision <= 8) {
					// ��ʱ��֧��QT6�����ϵİ汾
					msg("Unsupported metadata version:%d for %s @ %08X\n", revision, item_name, head);
				}
			}
		}
	}

	msg("[*] Search completed.\n");
	if (find_count == 0)
	{
		bool like = search_string_in_segment(".rdata", "?qt_metacall@");
		warning("No metadata entries were found%sou can debug this module and try again after it is initialized.",
			like ? ", but this module does look like a QT module. Y" : ". If you are sure that this is a QT module, y");
	}
}