CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 6043;
	title = 604302;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 4;
			elnk = 255;
			nextlnk = 253;
			prelnk = "100;";

			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = -1;
				cnt0 = 0;
				cnt2 = 0;
				ectype = -1;
				etype = 1;
				idx1 = -1;
				taid = 1;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "4;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "0;1;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 3;
			prelnk = "2;";
			nolnk = 255;
			rm = 0;
			yeslnk = 100;

			CDboTSCheckSToCEvt
			{
				itype = 0;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 604309;
				ctype = 1;
				idx = 7071104;
				taid = 1;
			}
			CDboTSActRegQInfo
			{
				cont = 604308;
				gtype = 3;
				area = 604301;
				goal = 604304;
				m0fz = "1151.000000";
				m0widx = 1;
				sort = 604305;
				stype = 8;
				m0fy = "-110.000000";
				grade = -1;
				m0fx = "4801.000000";
				m0ttip = 604315;
				rwd = 100;
				taid = 3;
				title = 604302;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 7513103;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 2;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 254;
			cid = 1;
			cont = 604308;
			gtype = 3;
			oklnk = 2;
			area = 604301;
			goal = 604304;
			sort = 604305;
			prelnk = "0;";
			ds = 1;
			grade = 0;
			rwd = 100;
			title = 604302;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 604314;
			nextlnk = 4;
			rwdtbl = 604301;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 7071104;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 604307;
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
				and = "6042;";
			}
		}
	}
}

