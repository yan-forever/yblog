import { useState, useEffect } from 'react'

function App() {
    // 初始化状态，用于存放从 C++ 后端抓取的数据库数据
    const [blogData, setBlogData] = useState({
        loading: true,
        title: '',
        content: '',
        error: null
    });

    useEffect(() => {
        // 这里的 IP 必须是你 Debian 服务器的真实地址
        // 端口 8080 是我们在后端 main.cpp 中 addListener 设定的
        fetch('http://10.182.190.32:8080/api/v1/status')
            .then((res) => {
                if (!res.ok) throw new Error(`HTTP error! status: ${res.status}`);
                return res.json();
            })
            .then((json) => {
                if (json.status === "success" && json.data) {
                    setBlogData({
                        loading: false,
                        title: json.data.title,
                        content: json.data.content,
                        error: null
                    });
                } else {
                    throw new Error(json.message || "数据格式错误");
                }
            })
            .catch((err) => {
                console.error("Fetch error:", err);
                setBlogData({
                    loading: false,
                    title: '',
                    content: '',
                    error: "无法连接到 yblog 后端内核"
                });
            });
    }, []);

    return (
        // 使用 Tailwind v4 的 CSS 变量和实用类构建响应式布局
        <div className="min-h-screen bg-[#0b0e14] text-slate-200 selection:bg-blue-500/30 font-sans">

            {/* 背景装饰：微弱的径向渐变，模拟深空感 */}
            <div className="fixed inset-0 bg-[radial-gradient(circle_at_50%_50%,rgba(17,24,39,1)_0%,rgba(11,14,20,1)_100%)] -z-10" />

            <main className="max-w-3xl mx-auto pt-20 px-6">
                {/* 顶部标题 */}
                <header className="mb-12 border-b border-slate-800 pb-8">
                    <h1 className="text-3xl font-bold tracking-tight text-white flex items-center gap-3">
                        <span className="w-2 h-8 bg-blue-500 rounded-full" />
                        YBLOG <span className="text-slate-500 font-light text-xl">/ Kernel v1.0</span>
                    </h1>
                    <p className="mt-2 text-slate-400">基于 C++ Drogon + React 19 的高性能全栈博客系统</p>
                </header>

                {/* 核心内容展示区 */}
                <section className="space-y-8">
                    {blogData.loading ? (
                        // 加载状态：使用 Tailwind 的 animate-pulse 模拟呼吸灯
                        <div className="animate-pulse space-y-4">
                            <div className="h-8 bg-slate-800 rounded w-3/4"></div>
                            <div className="h-32 bg-slate-800 rounded"></div>
                        </div>
                    ) : blogData.error ? (
                        // 错误提示
                        <div className="p-4 bg-red-900/20 border border-red-500/50 rounded-lg text-red-400">
                            [ 异常 ]: {blogData.error}
                        </div>
                    ) : (
                        // 数据库真实内容
                        <article className="group relative p-8 bg-slate-900/50 border border-slate-800 rounded-2xl hover:border-blue-500/50 transition-all duration-500">
                            <h2 className="text-2xl font-semibold text-white mb-4 group-hover:text-blue-400 transition-colors">
                                {blogData.title}
                            </h2>
                            <div className="prose prose-invert max-w-none text-slate-400 leading-relaxed">
                                {blogData.content}
                            </div>

                            {/* 装饰性标签 */}
                            <div className="mt-8 pt-6 border-t border-slate-800 flex items-center justify-between text-xs font-mono text-slate-500">
                                <span>SOURCE: MARIADB_REMOTE</span>
                                <span>STATUS: 200_OK</span>
                            </div>
                        </article>
                    )}
                </section>

                {/* 底部操作区 */}
                <footer className="mt-20 py-10 text-center border-t border-slate-800/50">
                    <button
                        onClick={() => window.location.reload()}
                        className="px-6 py-2 bg-blue-600 hover:bg-blue-500 text-white rounded-lg transition-all active:scale-95 shadow-[0_0_20px_rgba(37,99,235,0.3)]"
                    >
                        同步最新数据
                    </button>
                </footer>
            </main>
        </div>
    )
}

export default App