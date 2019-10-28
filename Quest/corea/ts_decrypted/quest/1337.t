CNtlTSTrigger
{
	sm = 1;
	sq = 1;
	rq = 0;
	tid = 1337;
	title = 133702;

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
				conv = 133709;
				ctype = 1;
				idx = 3331209;
				taid = 2;
			}
			CDboTSActRegQInfo
			{
				cont = 133708;
				gtype = 0;
				area = 133701;
				goal = 133704;
				grade = 132203;
				rwd = 100;
				sort = 133705;
				stype = 2;
				taid = 1;
				title = 133702;
			}
		}
		CDboTSContEnd
		{
			cid = 254;
			prelnk = "100;";
			type = 1;
		}
		CDboTSContReward
		{
			canclnk = 255;
			cid = 100;
			desc = 133714;
			nextlnk = 254;
			rwdtbl = 133701;
			rwdtype = 0;
			ltime = -1;
			prelnk = "2;";
			usetbl = 1;

			CDboTSClickNPC
			{
				npcidx = 4372211;
			}
		}
		CDboTSContEnd
		{
			cid = 253;
			prelnk = "0;1;252;";
			type = 0;
		}
		CDboTSContProposal
		{
			cancellnk = 253;
			cid = 1;
			cont = 133708;
			gtype = 0;
			oklnk = 2;
			area = 133701;
			goal = 133704;
			sort = 133705;
			prelnk = "0;";
			ds = 1;
			grade = 132203;
			rwd = 100;
			title = 133702;
		}
		CDboTSContStart
		{
			cid = 0;
			stdiag = 133707;
			nolnk = 253;
			rm = 0;
			yeslnk = 1;

			CDboTSClickNPC
			{
				npcidx = 3331209;
			}
			CDboTSCheckLvl
			{
				maxlvl = 53;
				minlvl = 45;
			}
			CDboTSCheckClrQst
			{
				and = "1336;";
			}
		}
		CDboTSContGAct
		{
			cid = 252;
			elnk = 255;
			nextlnk = 253;
			prelnk = "2;";
		}
	}
}

