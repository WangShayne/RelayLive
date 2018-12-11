/**
 * ���ļ���libLiveģ��Ψһ���⵼����ͷ�ļ�
 */
#pragma once

#ifdef LIBLIVE_EXPORTS
#define LIBLIVE_API __declspec(dllexport)
#else
#define LIBLIVE_API
#endif

enum FLV_FRAG_TYPE
{
    FLV_HEAD,
    FLV_FRAG
};

enum MP4_FRAG_TYPE
{
    MP4_HEAD,
    MP4_FRAG
};

/**
 * ���ݻص������ӿ�
 * ���ϲ�ʵ��һ���̳иýӿڵ���������RTP�����������
 */
struct IlibLiveCb
{
    /**
     * FLV���ݴ����ӿ�
     */
    virtual void push_flv_frame(FLV_FRAG_TYPE tag_type, char* frames, int frames_size) = 0;

    /**
     * TS���ݴ����ӿ�(HLS)
     */
    virtual void push_ts_stream(char* pBuff, int nBuffSize) = 0;

    /**
     * h264���������ӿ�
     */
    virtual void push_h264_stream(char* pBuff, int nBuffSize) = 0;

    /**
     * mp4���ݴ����ӿ�
     */
    virtual void push_mp4_stream(MP4_FRAG_TYPE eType, char* pBuff, int nBuffSize) = 0;

    /**
     * rtsp���ն˽���
     */
    virtual void stop() = 0;

    bool        m_bFlv;
    bool        m_bTs;
    bool        m_bH264;
    bool        m_bMp4;
    IlibLiveCb():m_bFlv(false),m_bTs(false),m_bH264(false),m_bMp4(false){}
};

struct LIBLIVE_API IlibLive
{
    virtual ~IlibLive(){}

    /**
     * ����һ��ӵ�б��ӿڹ��ܵ�ʵ��
     * return ʵ����ָ�룬ע��Ҫ���������ͷ�
     */
    static IlibLive* CreateObj();

    /**
     * ���ñ��ؼ�����IP�Ͷ˿�
     * @param[in] strIP ����IP
     * @param[in] nPort ������UDP�˿�
     */
    virtual void SetLocalAddr(string strIP, int nPort) = 0;

    /**
     * ���û���֡����
     * @param[in] nPacketNum ֡��������,��ֵԽ���ӳ�Խ�󣬵���Ӧ�Ը��������״��
     */
    virtual void SetCatchPacketNum(int nPacketNum) = 0;

    /** 
     * ����UDP�˿ڼ��� 
     */
    virtual void StartListen() = 0;

    /**
     * ���ûص���������
     * @param[in] pHandle �ص���������ָ��
     */
    virtual void SetCallback(IlibLiveCb* pHandle) = 0;
};