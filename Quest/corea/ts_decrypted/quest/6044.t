CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6044;
	title = 604402;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContStart
		{
			cid = 0;
			stdiag = 604407;
			nolnk = 254;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 7071104;
			}
			CDboTSCheckPCCls
			{
				clsflg = 64;
			}
			CDboTSCheckLvl
			{
				maxlvl = 100;
				minlvl = 30;
			}
			CDboTSCheckClrQst
			{
				and = "6043;";
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "1;0;";
			type = 0;
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 604409;
				ctype = 1;
				idx = 7071104;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 604408;
				gtype = 1;
				area = 604401;
				goal = 604404;
				grade = -1;
				rwd = 100;
				sort = 604405;
				stype = 8;
				taid = 1;
				title = 604402;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604408;
			gtype = 1;
			oklnk = 2;
			area = 604401;
			goal = 604404;
			sort = 604405;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604402;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 604414;
			nextlnk = 253;
			rwdtbl = 604401;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4371402;
			}
		}
	}
}

