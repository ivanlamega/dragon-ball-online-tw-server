CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 902;
	title = 90202;

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
		CDboTSContGAct
		{
			cid = 101;
			elnk = 255;
			nextlnk = 254;
			prelnk = "100;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 716;
				taid = 2;
				type = 1;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
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
		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 90209;
				ctype = 1;
				idx = 2951102;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 90208;
				gtype = 1;
				area = 90201;
				goal = 90204;
				grade = 132203;
				rwd = 100;
				sort = 90205;
				stype = 2;
				taid = 1;
				title = 90202;
			}
			CDboTSActSToCEvt
			{
				apptype = 0;
				cnt1 = 0;
				eitype = 2;
				idx0 = 716;
				cnt0 = 1;
				cnt2 = 0;
				ectype = -1;
				etype = 0;
				idx1 = -1;
				taid = 3;
				esctype = 0;
				idx2 = -1;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 90208;
			gtype = 1;
			oklnk = 2;
			area = 90201;
			goal = 90204;
			sort = 90205;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 90202;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 90214;
			nextlnk = 101;
			rwdtbl = 90201;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5061107;
			}
			CDboTSCheckQItem
			{
				ct = 0;
				icnt = 1;
				iidx = 716;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "101;";
			type = 1;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 90207;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 2951102;
			}
			CDboTSCheckLvl
			{
				maxlvl = 39;
				minlvl = 31;
			}
			CDboTSCheckClrQst
			{
				and = "901;";
			}
		}
	}
	CNtlTSGroup
	{
		gid = 254;

		CDboTSContEnd
		{
			cid = 254;
			prelnk = "2;1;";
			type = 0;
		}
		CDboTSContGCond
		{
			cid = 1;
			prelnk = "0;";
			nolnk = 254;
			rm = 0;
			yeslnk = 2;

			CDboTSCheckQItem
			{
				ct = 1;
				icnt = 1;
				iidx = 716;
			}
		}
		CDboTSContGAct
		{
			cid = 2;
			elnk = 255;
			nextlnk = 254;
			prelnk = "1;";

			CDboTSActQItem
			{
				icnt0 = 255;
				iprob0 = "1.000000";
				iidx0 = 716;
				taid = 1;
				type = 1;
			}
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 90207;
			nolnk = 255;
			rm = 0;
			yeslnk = 1;
		}
	}
}

