CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1709;
	title = 170902;

	CNtlTSGroup
	{
		gid = 0;

		CDboTSContGAct
		{
			cid = 2;
			elnk = 252;
			nextlnk = 100;
			prelnk = "1;";

			CDboTSActNPCConv
			{
				conv = 170909;
				ctype = 1;
				idx = 5041114;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 170908;
				gtype = 1;
				area = 170901;
				goal = 170904;
				grade = 132203;
				rwd = 100;
				sort = 170905;
				stype = 2;
				taid = 1;
				title = 170902;
			}
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 170914;
			nextlnk = 254;
			rwdtbl = 170901;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 5041115;
			}
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 170908;
			gtype = 1;
			oklnk = 2;
			area = 170901;
			goal = 170904;
			sort = 170905;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 170902;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 170907;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 5041114;
			}
			CDboTSCheckLvl
			{
				maxlvl = 58;
				minlvl = 50;
			}
			CDboTSCheckClrQst
			{
				and = "1703;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
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
			prelnk = "100;";
			type = 1;
		}
	}
}

