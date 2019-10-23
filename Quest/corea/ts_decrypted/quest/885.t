CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 885;
	title = 88502;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;252;1;";
			type = 0;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 88507;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2971106;
			}
			CDboTSCheckLvl
			{
				maxlvl = 37;
				minlvl = 29;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 88514;
			nextlnk = 101;
			rwdtbl = 88501;
			rwdtype = 0;
			ltime = -1;
			prelnk = "3;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 2971106;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 3;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 88509;
				ctype = 1;
				idx = 2971106;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 88508;
				gtype = 3;
				area = 88501;
				goal = 88504;
				m0fz = "-35.000000";
				m0widx = 3;
				sort = 88505;
				stype = 1;
				m0fy = "0.000000";
				grade = 132203;
				m0fx = "419.000000";
				m0ttip = 88515;
				rwd = 100;
				taid = 1;
				title = 88502;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 0;
				idx0 = 1712103;
				cnt0 = 30;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
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
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 88508;
			gtype = 3;
			oklnk = 2;
			area = 88501;
			goal = 88504;
			sort = 88505;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 88502;
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
	}
}

